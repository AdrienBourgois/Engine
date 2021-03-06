#include "Modules/Render/DirectX/Dx12.h"

#include <d3dcompiler.h>
#include "Modules/Render/DirectX/DX12Helper.h"
#include "Core/CoreType/Vertex.h"
#include "Maths/Mat4.h"

bool Module::Render::DirectX12::DirectX12::Initialize()
{
	return true;
}

bool Module::Render::DirectX12::DirectX12::CreatePipeline()
{
#ifdef _DEBUG
	ID3D12Debug* debug;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();
#endif

	Display::Window* window = Engine::GetInstance()->GetModule<Display::Window>();

	const unsigned int width = window->GetWidth();
	const unsigned int height = window->GetHeight();

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.Width    = static_cast<FLOAT>(width);
	viewport.Height   = static_cast<FLOAT>(height);

	scissorRect.left   = 0;
	scissorRect.top    = 0;
	scissorRect.right  = width;
	scissorRect.bottom = height;

	factory = new Dx12Factory();
	if (!factory->InitFactory())
		return false;

	factory->MakeDevice(&device);

	factory->MakeCommandQueue(&commandQueue);
	factory->MakeSwapChain(commandQueue, FRAME_BUFFER_COUNT, *window->GetHandle(), width, height, window->IsFullscreen(), &swapChain);
	factory->MakeRenderTargetView(FRAME_BUFFER_COUNT, swapChain, &renderTargetDescriptorHeap, &renderTargetDescriptorSize, renderTargets);
	factory->MakeCommandAllocator(FRAME_BUFFER_COUNT, commandAllocator);
	factory->MakeCommandList(commandAllocator[0], &preRenderCommandList);
	factory->MakeCommandList(commandAllocator[0], &postRenderCommandList);
	factory->MakeFence(FRAME_BUFFER_COUNT, fence, fenceValue, &fenceEvent);
	factory->MakeRootSignature(&rootSignature);
	factory->MakeVertexShader(L"Content\\Core\\Shaders\\VertexShader.hlsl", &vertexShaderBytecode);
	factory->MakePixelShader(L"Content\\Core\\Shaders\\PixelShader.hlsl", &pixelShaderBytecode);
	factory->MakeDepthStencilBuffer(&depthStencilDescriptorHeap, &depthStencilBuffer, width, height);
	factory->MakePipelineStateObject(rootSignature, &vertexShaderBytecode, &pixelShaderBytecode, &pipelineStateObject);

	preRenderCommandList->SetName(L"Pre-Render Command List");
	postRenderCommandList->SetName(L"Post-Render Command List");

	return true;
}

bool Module::Render::DirectX12::DirectX12::Render()
{
	UpdatePipeline();
	PreRender();

	ID3D12CommandList** pp_command_lists = new ID3D12CommandList*[graphicsObjects.size() + 2];

	pp_command_lists[0] = preRenderCommandList;

	unsigned int i = 0;
	for (const std::pair<const int, Objects::Dx12GraphicObject*> object_command_list : graphicsObjects)
	{
		pp_command_lists[i + 1] = object_command_list.second->GetCommandList();
		++i;
	}
	pp_command_lists[i + 1] = postRenderCommandList;

	commandQueue->ExecuteCommandLists(static_cast<UINT>(graphicsObjects.size()) + 2, pp_command_lists);

	FlushCommandQueue();

	TRYFUNC(swapChain->Present(0, 0));

	delete[] pp_command_lists;

	PostRender();

	return true;
}

bool Module::Render::DirectX12::DirectX12::UpdatePipeline()
{
	frameIndex = swapChain->GetCurrentBackBufferIndex();

	return true;
}

bool Module::Render::DirectX12::DirectX12::PreRender()
{
	TRYFUNC(commandAllocator[frameIndex]->Reset());

	PreparePreRenderCommandList();
	for (const std::pair<const int, Objects::Dx12GraphicObject*> pair : graphicsObjects)
	{
		PrepareObjectCommandList(pair.second);
	}
	PreparePostRenderCommandList();

	return true;
}

bool Module::Render::DirectX12::DirectX12::PostRender() const
{
	return true;
}

bool Module::Render::DirectX12::DirectX12::Cleanup()
{
	FlushCommandQueue();
	CloseHandle(fenceEvent);

	BOOL fullscreen = false;
	swapChain->GetFullscreenState(&fullscreen, nullptr);
	if (fullscreen)
		swapChain->SetFullscreenState(false, nullptr);

	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(commandQueue);
	SAFE_RELEASE(preRenderCommandList);
	SAFE_RELEASE(postRenderCommandList);

	for (std::pair<const int, Objects::Dx12GraphicObject*> object : graphicsObjects)
		delete object.second;

	SAFE_RELEASE(pipelineStateObject);
	SAFE_RELEASE(rootSignature);

	SAFE_RELEASE(renderTargetDescriptorHeap);

	SAFE_RELEASE(depthStencilBuffer);
	SAFE_RELEASE(depthStencilDescriptorHeap);

	for (int i = 0; i < FRAME_BUFFER_COUNT; ++i)
	{
		SAFE_RELEASE(renderTargets[i]);
		SAFE_RELEASE(commandAllocator[i]);
		SAFE_RELEASE(fence[i]);
	}

	delete factory;

#ifdef _DEBUG
	ID3D12DebugDevice1* debug_device;
	device->QueryInterface(IID_PPV_ARGS(&debug_device));
	debug_device->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL);
#endif
	SAFE_RELEASE(device);

	return true;
}

bool Module::Render::DirectX12::DirectX12::CreateBuffers(const unsigned int _id, Core::CoreType::String _name, Core::CoreType::Transform* _transform, Core::CoreType::Vertex* _vertices_array, const unsigned int _vertices_count, unsigned int* _indexs_array, const unsigned int _indexs_count)
{
	ID3D12GraphicsCommandList* command_list = nullptr;
	factory->MakeCommandList(commandAllocator[frameIndex], &command_list);

	D3D12_VERTEX_BUFFER_VIEW* buffer_view = nullptr;
	const Dx12CommandExecutionPack pack = { pipelineStateObject, commandAllocator[frameIndex], commandQueue, fence[frameIndex], &fenceValue[frameIndex] };
	factory->CreateVertexBuffer(pack, _name, _vertices_array, _vertices_count, command_list, &buffer_view);

	D3D12_INDEX_BUFFER_VIEW* index_view = nullptr;
	if (_indexs_array && _indexs_count)
		factory->CreateIndexBuffer(pack, _name, _indexs_array, _indexs_count, command_list, &index_view);

	Objects::Dx12ConstantBuffer* constant_buffer;
	factory->CreateConstantBuffer(&Math::Mat4::Identity, &constant_buffer);

	graphicsObjects[_id] = new Objects::Dx12GraphicObject(_id, _name, _transform, command_list, _vertices_array, _vertices_count, buffer_view, _indexs_array, _indexs_count, index_view, constant_buffer);

	return true;
}

void Module::Render::DirectX12::DirectX12::SetCameraViewMatrix(const Math::Mat4 _camera_view)
{
	cameraViewMatrix = _camera_view;
}

void Module::Render::DirectX12::DirectX12::SetCameraProjectionMatrix(const Math::Mat4 _camera_projection)
{
	cameraProjectionMatrix = _camera_projection;
}

bool Module::Render::DirectX12::DirectX12::FlushCommandQueue()
{
	fenceValue[frameIndex]++;

	TRYFUNC(commandQueue->Signal(fence[frameIndex], fenceValue[frameIndex]));

	if (fence[frameIndex]->GetCompletedValue() < fenceValue[frameIndex])
	{
		TRYFUNC(fence[frameIndex]->SetEventOnCompletion(fenceValue[frameIndex], fenceEvent));

		WaitForSingleObject(fenceEvent, INFINITE);
	}

	return true;
}

bool Module::Render::DirectX12::DirectX12::PreparePreRenderCommandList()
{
	TRYFUNC(preRenderCommandList->Reset(commandAllocator[frameIndex], pipelineStateObject));

	CD3DX12_RESOURCE_BARRIER present_to_target_barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	preRenderCommandList->ResourceBarrier(1, &present_to_target_barrier);

	CD3DX12_CPU_DESCRIPTOR_HANDLE render_target_view_handle(renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, renderTargetDescriptorSize);
	CD3DX12_CPU_DESCRIPTOR_HANDLE depth_stencil_view_handle(depthStencilDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	preRenderCommandList->OMSetRenderTargets(1, &render_target_view_handle, FALSE, &depth_stencil_view_handle);

	float clear_color[4];
	Core::CoreType::Color::FillArrayColor(clear_color, Core::CoreType::Color::Turquoise);
	preRenderCommandList->ClearRenderTargetView(render_target_view_handle, clear_color, 0, nullptr);
	preRenderCommandList->ClearDepthStencilView(depthStencilDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	preRenderCommandList->SetGraphicsRootSignature(rootSignature);

	TRYFUNC(preRenderCommandList->Close());

	return true;
}

bool Module::Render::DirectX12::DirectX12::PreparePostRenderCommandList()
{
	TRYFUNC(postRenderCommandList->Reset(commandAllocator[frameIndex], pipelineStateObject));

	CD3DX12_RESOURCE_BARRIER target_to_present_barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	postRenderCommandList->ResourceBarrier(1, &target_to_present_barrier);

	TRYFUNC(postRenderCommandList->Close());

	return true;
}

bool Module::Render::DirectX12::DirectX12::PrepareObjectCommandList(Objects::Dx12GraphicObject* _graphic_object)
{
	Math::Mat4 wvs_matrix = (_graphic_object->GetTransform()->GetWorldMatrix() * cameraViewMatrix * cameraProjectionMatrix).GetTranspose();
	const auto virtual_gpu_adress = _graphic_object->GetConstantBuffer()->Map();
	memcpy(virtual_gpu_adress, &wvs_matrix, sizeof wvs_matrix);
	_graphic_object->GetConstantBuffer()->Unmap();

	ID3D12GraphicsCommandList* command_list = _graphic_object->GetCommandList();

	TRYFUNC(command_list->Reset(commandAllocator[frameIndex], pipelineStateObject));

	CD3DX12_CPU_DESCRIPTOR_HANDLE render_target_view_handle(renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, renderTargetDescriptorSize);
	CD3DX12_CPU_DESCRIPTOR_HANDLE depth_stencil_view_handle(depthStencilDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	command_list->OMSetRenderTargets(1, &render_target_view_handle, FALSE, &depth_stencil_view_handle);

	command_list->SetGraphicsRootSignature(rootSignature);
	command_list->RSSetViewports(1, &viewport);
	command_list->RSSetScissorRects(1, &scissorRect);

	_graphic_object->PrepareCommandList();
	TRYFUNC(command_list->Close());

	return true;
}
