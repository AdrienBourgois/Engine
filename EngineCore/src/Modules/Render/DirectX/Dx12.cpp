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
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.Width    = static_cast<FLOAT>(MODULE(Display::Window)->getWidth());
	viewport.Height   = static_cast<FLOAT>(MODULE(Display::Window)->getHeight());

	scissorRect.left   = 0;
	scissorRect.top    = 0;
	scissorRect.right  = MODULE(Display::Window)->getWidth();
	scissorRect.bottom = MODULE(Display::Window)->getHeight();

	factory = new Dx12Factory();
	if (!factory->InitFactory())
		return false;

	factory->MakeDevice(&device);
	factory->MakeCommandQueue(&commandQueue);
	factory->MakeSwapChain(commandQueue,FRAME_BUFFER_COUNT, *MODULE(Display::Window)->getHandle(), MODULE(Display::Window)->getWidth(), MODULE(Display::Window)->getHeight(), MODULE(Display::Window)->isFullscreen(), commandQueue, &swapChain);
	factory->MakeDescriptorHeap(FRAME_BUFFER_COUNT, swapChain, &rtvDescriptorHeap, &rtvDescriptorSize, renderTargets);
	factory->MakeCommandAllocator(FRAME_BUFFER_COUNT, commandAllocator);
	factory->MakeCommandList(commandAllocator[0], &preRenderCommandList);
	factory->MakeCommandList(commandAllocator[0], &postRenderCommandList);
	factory->MakeFence(FRAME_BUFFER_COUNT, fence, fenceValue, &fenceEvent);
	factory->MakeRootSignature(&rootSignature);
	factory->MakeVertexShader(L"Content\\Core\\Shaders\\VertexShader.hlsl", &vertexShaderBytecode);
	factory->MakePixelShader(L"Content\\Core\\Shaders\\PixelShader.hlsl", &pixelShaderBytecode);
	factory->MakePipelineStateObject(rootSignature, &vertexShaderBytecode, &pixelShaderBytecode, &pipelineStateObject);

	preRenderCommandList->SetName(L"Pre-Render Command List");
	postRenderCommandList->SetName(L"Post-Render Command List");

	return true;
}

bool Module::Render::DirectX12::DirectX12::UpdatePipeline()
{
	WaitForPreviousFrame();

	TRYFUNC(commandAllocator[frameIndex]->Reset());

	PreparePreRenderCommandList();
	for (std::pair<const int, Objects::Dx12GraphicObject*> object : graphicsObjects)
		PrepareObjectCommandList(object.second);
	PreparePostRenderCommandList();

	return true;
}

bool Module::Render::DirectX12::DirectX12::Render()
{
	UpdatePipeline();

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

	return true;
}

bool Module::Render::DirectX12::DirectX12::Cleanup()
{
	WaitForPreviousFrame();
	CloseHandle(fenceEvent);

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

	SAFE_RELEASE(rtvDescriptorHeap);

	for (int i = 0; i < FRAME_BUFFER_COUNT; ++i)
	{
		SAFE_RELEASE(renderTargets[i]);
		SAFE_RELEASE(commandAllocator[i]);
		SAFE_RELEASE(fence[i]);
	};

	if (factory)
		delete factory;

	return true;
}

bool Module::Render::DirectX12::DirectX12::CreateVertexBuffer(int _id, const Core::CoreType::Vertex* _vertex, int _size, Core::CoreType::String _name)
{
	ID3D12GraphicsCommandList* command_list = nullptr;
	factory->MakeCommandList(commandAllocator[frameIndex], &command_list);

	TRYFUNC(command_list->Reset(commandAllocator[frameIndex], pipelineStateObject));

	Core::CoreType::Vertex* vertex_list = new Core::CoreType::Vertex[_size];

	for (int i = 0; i < _size; ++i)
		vertex_list[i] = _vertex[i];

	int buffer_size = _size * sizeof(Core::CoreType::Vertex);

	CD3DX12_HEAP_PROPERTIES default_heap_properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_HEAP_PROPERTIES upload_heap_properties  = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC buffer_size_desc          = CD3DX12_RESOURCE_DESC::Buffer(buffer_size);

	ID3D12Resource* vertex_buffer = nullptr;
	device->CreateCommittedResource(&default_heap_properties, D3D12_HEAP_FLAG_NONE, &buffer_size_desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&vertex_buffer));
	vertex_buffer->SetName((_name + S(" - Buffer")).ToWideString());

	ID3D12Resource* vBufferUploadHeap;
	device->CreateCommittedResource(&upload_heap_properties, D3D12_HEAP_FLAG_NONE, &buffer_size_desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vBufferUploadHeap));
	vBufferUploadHeap->SetName((_name + S(" - Upload")).ToWideString());

	D3D12_SUBRESOURCE_DATA vertexData;
	vertexData.pData                  = reinterpret_cast<BYTE*>(vertex_list);
	vertexData.RowPitch               = buffer_size;
	vertexData.SlicePitch             = buffer_size;

	UpdateSubresources(command_list, vertex_buffer, vBufferUploadHeap, 0, 0, 1, &vertexData);

	CD3DX12_RESOURCE_BARRIER transition_barrier = CD3DX12_RESOURCE_BARRIER::Transition(vertex_buffer, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	command_list->ResourceBarrier(1, &transition_barrier);

	command_list->Close();
	ID3D12CommandList* ppCommandLists[] = { command_list };
	commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	fenceValue[frameIndex]++;
	TRYFUNC(commandQueue->Signal(fence[frameIndex], fenceValue[frameIndex]));
	fence[frameIndex]->SetEventOnCompletion(fenceValue[frameIndex], fenceEvent);
	WaitForSingleObject(fenceEvent, INFINITE);

	D3D12_VERTEX_BUFFER_VIEW* buffer_view = new D3D12_VERTEX_BUFFER_VIEW;
	buffer_view->BufferLocation = vertex_buffer->GetGPUVirtualAddress();
	buffer_view->StrideInBytes  = sizeof(Core::CoreType::Vertex);
	buffer_view->SizeInBytes    = buffer_size;

	delete[] vertex_list;

	graphicsObjects[_id] = new Objects::Dx12GraphicObject(_id, _vertex, _name, command_list, buffer_view);

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

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorSize);

	preRenderCommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	preRenderCommandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

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

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorSize);

	command_list->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	command_list->SetGraphicsRootSignature(rootSignature);
	command_list->RSSetViewports(1, &viewport);
	command_list->RSSetScissorRects(1, &scissorRect);

	_graphic_object->PrepareCommandList();

	TRYFUNC(command_list->Close());

	return true;
}
