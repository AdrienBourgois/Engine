#include "Modules/Render/DirectX/Dx12.h"

#include <D3Dcompiler.h>
#include "Modules/Render/DirectX/DX12Helper.h"
#include "Core/CoreType/Vertex.h"
#include "Core/CoreType/Id.h"
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
	factory->MakeCommandList(commandAllocator[0], &resourcesRenderCommandList);
	factory->MakeFence(FRAME_BUFFER_COUNT, fence, fenceValue, &fenceEvent);
	factory->MakeRootSignature(&rootSignature);
	factory->MakeVertexShader(L"Content\\Core\\Shaders\\VertexShader.hlsl", &vertexShaderBytecode);
	factory->MakePixelShader(L"Content\\Core\\Shaders\\PixelShader.hlsl", &pixelShaderBytecode);
	factory->MakePipelineStateObject(rootSignature, &vertexShaderBytecode, &pixelShaderBytecode, &pipelineStateObject);

	Core::CoreType::Vertex point1 = Core::CoreType::Vertex(Math::Vec3(0.f, .5f, .5f), Core::CoreType::Color::Red);
	Core::CoreType::Vertex point2 = Core::CoreType::Vertex(Math::Vec3(.5f, -.5f, .5f), Core::CoreType::Color::Blue);
	Core::CoreType::Vertex point3 = Core::CoreType::Vertex(Math::Vec3(-.5f, -.5f, .5f), Core::CoreType::Color::Green);

	Core::CoreType::Vertex point4 = Core::CoreType::Vertex(Math::Vec3(0.f, -.5f, .5f), Core::CoreType::Color::White);
	Core::CoreType::Vertex point5 = Core::CoreType::Vertex(Math::Vec3(-.5f, .5f, .5f), Core::CoreType::Color::Black);
	Core::CoreType::Vertex point6 = Core::CoreType::Vertex(Math::Vec3(.5f, .5f, .5f), Core::CoreType::Color::Red);

	Core::CoreType::Vertex triangle[] = { point1, point2, point3 };
	Core::CoreType::Vertex triangle2[] = { point4, point5, point6 };

	Object::Component::GraphicComponent object1(triangle, 3);
	Object::Component::GraphicComponent object2(triangle2, 3);

	MakeVertexBuffer(object1.GetId().GetInstanceNumber(), object1.GetPoints(), object1.GetSize(), L"Triangle 1");
	MakeVertexBuffer(object2.GetId().GetInstanceNumber(), object2.GetPoints(), object2.GetSize(), L"Triangle 2");

	return true;
}

bool Module::Render::DirectX12::DirectX12::UpdatePipeline()
{
	WaitForPreviousFrame();

	TRYFUNC(commandAllocator[frameIndex]->Reset());

	PreparePreRenderCommandList();

	for (int i = 0; i < objectCommandLists.size(); ++i)
		PrepareObjectCommandList(i);

	PreparePostRenderCommandList();

	return true;
}

bool Module::Render::DirectX12::DirectX12::Render()
{
	UpdatePipeline();

	ID3D12CommandList** ppCommandLists = new ID3D12CommandList*[2];

	//ppCommandLists[0] = resourcesRenderCommandList;
	ppCommandLists[0] = preRenderCommandList;
	/*for (std::pair<const int, struct ID3D12GraphicsCommandList*> object_command_list : objectCommandLists)
		ppCommandLists.push_back(object_command_list.second);*/
	ppCommandLists[1] = postRenderCommandList;

	commandQueue->ExecuteCommandLists(2, ppCommandLists);

	TRYFUNC(commandQueue->Signal(fence[frameIndex], fenceValue[frameIndex]));

	TRYFUNC(swapChain->Present(0, 0));

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
	SAFE_RELEASE(resourcesRenderCommandList);

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

bool Module::Render::DirectX12::DirectX12::MakeVertexBuffer(int _id, const Core::CoreType::Vertex* _vertex, UINT _size, LPCWSTR _name)
{
	TRYFUNC(resourcesRenderCommandList->Reset(commandAllocator[frameIndex], pipelineStateObject));

	Core::CoreType::Vertex* vertex_list = new Core::CoreType::Vertex[_size];

	for (UINT i = 0; i < _size; ++i)
		vertex_list[i] = _vertex[i];

	int buffer_size = _size * sizeof(Core::CoreType::Vertex);

	CD3DX12_HEAP_PROPERTIES default_heap_properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_HEAP_PROPERTIES upload_heap_properties  = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC buffer_size_desc          = CD3DX12_RESOURCE_DESC::Buffer(buffer_size);

	ID3D12Resource* vertex_buffer = nullptr;
	device->CreateCommittedResource(&default_heap_properties, D3D12_HEAP_FLAG_NONE, &buffer_size_desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&vertex_buffer));
	vertex_buffer->SetName(_name);

	ID3D12Resource* vBufferUploadHeap;
	device->CreateCommittedResource(&upload_heap_properties, D3D12_HEAP_FLAG_NONE, &buffer_size_desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vBufferUploadHeap));
	vBufferUploadHeap->SetName(_name);

	D3D12_SUBRESOURCE_DATA vertexData;
	vertexData.pData                  = reinterpret_cast<BYTE*>(vertex_list);
	vertexData.RowPitch               = buffer_size;
	vertexData.SlicePitch             = buffer_size;

	UpdateSubresources(resourcesRenderCommandList, vertex_buffer, vBufferUploadHeap, 0, 0, 1, &vertexData);

	CD3DX12_RESOURCE_BARRIER transition_barrier = CD3DX12_RESOURCE_BARRIER::Transition(vertex_buffer, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	resourcesRenderCommandList->ResourceBarrier(1, &transition_barrier);

	resourcesRenderCommandList->Close();
	ID3D12CommandList* ppCommandLists[] = { resourcesRenderCommandList };
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

	vertexBufferViews.insert_or_assign(_id, buffer_view);

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

bool Module::Render::DirectX12::DirectX12::PrepareObjectCommandList(int _objectCommandListNumber)
{
	ID3D12GraphicsCommandList* command_list = objectCommandLists[_objectCommandListNumber];

	TRYFUNC(command_list->Reset(commandAllocator[frameIndex], pipelineStateObject));

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorSize);

	command_list->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	command_list->SetGraphicsRootSignature(rootSignature);
	command_list->RSSetViewports(1, &viewport);
	command_list->RSSetScissorRects(1, &scissorRect);
	command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	command_list->IASetVertexBuffers(0, 1, vertexBufferViews[_objectCommandListNumber]);
	command_list->DrawInstanced(3, 1, 0, 0);

	TRYFUNC(command_list->Close());

	return true;
}
