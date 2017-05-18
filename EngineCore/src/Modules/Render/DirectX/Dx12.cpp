#include "Modules/Render/DirectX/Dx12.h"

#include <D3Dcompiler.h>
#include "Modules/Render/DirectX/DX12Helper.h"
#include "Core/CoreType/Vertex.h"
#include "Objects/Components/GraphicComponent.h"

bool Module::Render::DirectX12::DirectX12::Initialize()
{
	return true;
}

bool Module::Render::DirectX12::DirectX12::CreatePipeline()
{
	unsigned int width = MODULE(Display::Window)->getWidth();
	unsigned int height = MODULE(Display::Window)->getHeight();

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

	rootSignatureSerializer = new Objects::Dx12RootSignatureDescritor();

	factory->MakeDevice(&device);

	/* --------------------------------------- */

	rootSignatureSerializer->CreateTable();
	factory->CreateConstantBuffer(&colorMultiplier, &colorConstantBuffer);

	/* --------------------------------------- */

	factory->MakeCommandQueue(&commandQueue);
	factory->MakeSwapChain(commandQueue, FRAME_BUFFER_COUNT, *MODULE(Display::Window)->getHandle(), width, height, MODULE(Display::Window)->isFullscreen(), &swapChain);
	factory->MakeDescriptorHeap(FRAME_BUFFER_COUNT, swapChain, &renderTargetDescriptorHeap, &renderTargetDescriptorSize, renderTargets);
	factory->MakeCommandAllocator(FRAME_BUFFER_COUNT, commandAllocator);
	factory->MakeCommandList(commandAllocator[0], &preRenderCommandList);
	factory->MakeCommandList(commandAllocator[0], &postRenderCommandList);
	factory->MakeFence(FRAME_BUFFER_COUNT, fence, fenceValue, &fenceEvent);
	factory->MakeRootSignature(rootSignatureSerializer->GetSignature(), &rootSignature);
	factory->MakeVertexShader(L"Content\\Core\\Shaders\\VertexShader.hlsl", &vertexShaderBytecode);
	factory->MakePixelShader(L"Content\\Core\\Shaders\\PixelShader.hlsl", &pixelShaderBytecode);
	factory->MakeDepthStencilBuffer(&depthStencilDescriptorHeap, &depthStencilBuffer, width, height);
	factory->MakePipelineStateObject(rootSignature, &vertexShaderBytecode, &pixelShaderBytecode, &pipelineStateObject);

	rootSignatureSerializer->SignatureUpdated();

	preRenderCommandList->SetName(L"Pre-Render Command List");
	postRenderCommandList->SetName(L"Post-Render Command List");

	return true;
}

bool Module::Render::DirectX12::DirectX12::Render()
{
	UpdatePipeline();
	PreRender();

	ID3D12CommandList** ppCommandLists = new ID3D12CommandList*[graphicsObjects.size() + 2];

	ppCommandLists[0] = preRenderCommandList;

	unsigned int i = 0;
	for (std::pair<const int, Objects::Dx12GraphicObject*> object_command_list : graphicsObjects)
	{
		ppCommandLists[i + 1] = object_command_list.second->GetCommandList();
		++i;
	}
	ppCommandLists[i + 1] = postRenderCommandList;

	commandQueue->ExecuteCommandLists(static_cast<UINT>(graphicsObjects.size()) + 2, ppCommandLists);

	TRYFUNC(commandQueue->Signal(fence[frameIndex], fenceValue[frameIndex]));

	TRYFUNC(swapChain->Present(0, 0));

	delete[] ppCommandLists;

	PostRender();

	return true;
}

bool Module::Render::DirectX12::DirectX12::UpdatePipeline()
{
	bool need_new_pso = false;

	if(rootSignatureSerializer->IsUpdateNeeded())
	{
		factory->MakeRootSignature(rootSignatureSerializer->GetSignature(), &rootSignature);
		rootSignatureSerializer->SignatureUpdated();
		need_new_pso = true;
	}

	if(need_new_pso)
		factory->MakePipelineStateObject(rootSignature, &vertexShaderBytecode, &pixelShaderBytecode, &pipelineStateObject);

	return true;
}

bool Module::Render::DirectX12::DirectX12::PreRender()
{
	WaitForPreviousFrame();

	TRYFUNC(commandAllocator[frameIndex]->Reset());

	/* ---------------------------------------- */

	static float rIncrement = 0.00002f;
	static float gIncrement = 0.00006f;
	static float bIncrement = 0.00009f;

	colorMultiplier.r += rIncrement;
	colorMultiplier.g += gIncrement;
	colorMultiplier.b += bIncrement;

	if (colorMultiplier.r >= 1.0f || colorMultiplier.r <= 0.0f)
	{
		colorMultiplier.r = colorMultiplier.r >= 1.0f ? 1.0f : 0.0f;
		rIncrement = -rIncrement;
	}
	if (colorMultiplier.g >= 1.0f || colorMultiplier.g <= 0.0f)
	{
		colorMultiplier.g = colorMultiplier.g >= 1.0f ? 1.0f : 0.0f;
		gIncrement = -gIncrement;
	}
	if (colorMultiplier.b >= 1.0f || colorMultiplier.b <= 0.0f)
	{
		colorMultiplier.b = colorMultiplier.b >= 1.0f ? 1.0f : 0.0f;
		bIncrement = -bIncrement;
	}

	memcpy(reinterpret_cast<void**>(colorConstantBuffer->Map()), &colorMultiplier, sizeof colorMultiplier);
	colorConstantBuffer->Unmap();

	/* ---------------------------------------- */

	PreparePreRenderCommandList();
	for (std::pair<const int, Objects::Dx12GraphicObject*> object : graphicsObjects)
		PrepareObjectCommandList(object.second);
	PreparePostRenderCommandList();

	return true;
}

bool Module::Render::DirectX12::DirectX12::PostRender()
{
	return true;
}

bool Module::Render::DirectX12::DirectX12::Cleanup()
{
	WaitForPreviousFrame();
	CloseHandle(fenceEvent);

	delete colorConstantBuffer;

	BOOL fs = false;
	if (swapChain->GetFullscreenState(&fs, nullptr))
		swapChain->SetFullscreenState(false, nullptr);

	SAFE_RELEASE(device);
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

	if (factory)
		delete factory;

	return true;
}

bool Module::Render::DirectX12::DirectX12::CreateBuffers(unsigned int _id, Core::CoreType::String _name, Core::CoreType::Vertex* _vertices_array, unsigned int _vertices_count, unsigned int* _indexs_array, unsigned int _indexs_count)
{
	ID3D12GraphicsCommandList* command_list = nullptr;
	factory->MakeCommandList(commandAllocator[frameIndex], &command_list);

	D3D12_VERTEX_BUFFER_VIEW* buffer_view = nullptr;
	Dx12CommandExecutionPack pack = { pipelineStateObject, commandAllocator[frameIndex], commandQueue, fence[frameIndex], &fenceValue[frameIndex] };
	factory->CreateVertexBuffer(pack, _name, _vertices_array, _vertices_count, command_list, &buffer_view);

	D3D12_INDEX_BUFFER_VIEW* index_view = nullptr;
	if (_indexs_array && _indexs_count)
		factory->CreateIndexBuffer(pack, _name, _indexs_array, _indexs_count, command_list, &index_view);

	graphicsObjects[_id] = new Objects::Dx12GraphicObject(_id, _name, command_list, _vertices_array, _vertices_count, buffer_view, _indexs_array, _indexs_count, index_view);

	return true;
}

bool Module::Render::DirectX12::DirectX12::WaitForPreviousFrame()
{
	frameIndex = swapChain->GetCurrentBackBufferIndex();

	if (fence[frameIndex]->GetCompletedValue() < fenceValue[frameIndex])
	{
		TRYFUNC(fence[frameIndex]->SetEventOnCompletion(fenceValue[frameIndex], fenceEvent));

		WaitForSingleObject(fenceEvent, INFINITE);
	}

	fenceValue[frameIndex]++;

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
	FillArrayColor(clear_color, Core::CoreType::Color::Sgiolivedrab);
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
	ID3D12GraphicsCommandList* command_list = _graphic_object->GetCommandList();

	TRYFUNC(command_list->Reset(commandAllocator[frameIndex], pipelineStateObject));

	CD3DX12_CPU_DESCRIPTOR_HANDLE render_target_view_handle(renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, renderTargetDescriptorSize);
	CD3DX12_CPU_DESCRIPTOR_HANDLE depth_stencil_view_handle(depthStencilDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	command_list->OMSetRenderTargets(1, &render_target_view_handle, FALSE, &depth_stencil_view_handle);

	command_list->SetGraphicsRootSignature(rootSignature);
	command_list->RSSetViewports(1, &viewport);
	command_list->RSSetScissorRects(1, &scissorRect);

	/* ----------------------------------- */

	ID3D12DescriptorHeap* descriptorHeaps[] = { colorConstantBuffer->GetDescriptorHeap() };
	command_list->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	command_list->SetGraphicsRootDescriptorTable(0, colorConstantBuffer->GetDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	/* ----------------------------------- */

	_graphic_object->PrepareCommandList();
	TRYFUNC(command_list->Close());

	return true;
}
