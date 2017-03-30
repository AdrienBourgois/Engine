#include "Modules/Render/DirectX/Dx12.h"

#include <D3Dcompiler.h>
#include "Modules/Render/DirectX/DX12Helper.h"
#include "Core/CoreType/Vertex.h"

void Module::Render::DirectX12::DirectX12::MakeVertexBuffer()
{
	Core::CoreType::Vertex point1 = Core::CoreType::Vertex(Math::Vec3(0.f, .5f, .5f), Core::CoreType::Color::White);
	point1.SetColor(Core::CoreType::Color::Black);

	Core::CoreType::Vertex vList[] = {
		point1,
		{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	};

	int vBufferSize = sizeof(vList);

	CD3DX12_HEAP_PROPERTIES default_heap_properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_HEAP_PROPERTIES upload_heap_properties  = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC buffer_size_desc          = CD3DX12_RESOURCE_DESC::Buffer(vBufferSize);

	device->CreateCommittedResource(&default_heap_properties, D3D12_HEAP_FLAG_NONE, &buffer_size_desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&vertexBuffer));
	vertexBuffer->SetName(L"Vertex Buffer Resource Heap");

	ID3D12Resource* vBufferUploadHeap;
	device->CreateCommittedResource(&upload_heap_properties, D3D12_HEAP_FLAG_NONE, &buffer_size_desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vBufferUploadHeap));
	vBufferUploadHeap->SetName(L"Vertex Buffer Upload Resource Heap");

	D3D12_SUBRESOURCE_DATA vertexData = {};
	vertexData.pData                  = reinterpret_cast<BYTE*>(vList);
	vertexData.RowPitch               = vBufferSize;
	vertexData.SlicePitch             = vBufferSize;

	UpdateSubresources(commandList, vertexBuffer, vBufferUploadHeap, 0, 0, 1, &vertexData);

	CD3DX12_RESOURCE_BARRIER transition_barrier = CD3DX12_RESOURCE_BARRIER::Transition(vertexBuffer, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	commandList->ResourceBarrier(1, &transition_barrier);

	commandList->Close();
	ID3D12CommandList* ppCommandLists[] = { commandList };
	commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	fenceValue[frameIndex]++;
	TRYFUNC(commandQueue->Signal(fence[frameIndex], fenceValue[frameIndex]));

	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.StrideInBytes  = sizeof(Core::CoreType::Vertex);
	vertexBufferView.SizeInBytes    = vBufferSize;
}

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
	frameIndex = swapChain->GetCurrentBackBufferIndex();
	factory->MakeDescriptorHeap(FRAME_BUFFER_COUNT, swapChain, &rtvDescriptorHeap, &rtvDescriptorSize, renderTargets);
	factory->MakeCommandList(FRAME_BUFFER_COUNT, commandAllocator, &commandList);
	factory->MakeFence(FRAME_BUFFER_COUNT, fence, fenceValue, &fenceEvent);
	factory->MakeRootSignature(&rootSignature);
	factory->MakeVertexShader(L"Content\\Core\\Shaders\\VertexShader.hlsl", &vertexShaderBytecode);
	factory->MakePixelShader(L"Content\\Core\\Shaders\\PixelShader.hlsl", &pixelShaderBytecode);
	factory->MakePipelineStateObject(rootSignature, &vertexShaderBytecode, &pixelShaderBytecode, &pipelineStateObject);
	MakeVertexBuffer();

	return true;
}

bool Module::Render::DirectX12::DirectX12::UpdatePipeline()
{
	WaitForPreviousFrame();

	TRYFUNC(commandAllocator[frameIndex]->Reset());

	TRYFUNC(commandList->Reset(commandAllocator[frameIndex], pipelineStateObject));

	CD3DX12_RESOURCE_BARRIER present_to_target_barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	commandList->ResourceBarrier(1, &present_to_target_barrier);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorSize);

	commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	commandList->SetGraphicsRootSignature(rootSignature);
	commandList->RSSetViewports(1, &viewport);
	commandList->RSSetScissorRects(1, &scissorRect);
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
	commandList->DrawInstanced(3, 1, 0, 0);

	CD3DX12_RESOURCE_BARRIER target_to_present_barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	commandList->ResourceBarrier(1, &target_to_present_barrier);

	TRYFUNC(commandList->Close());

	return true;
}

bool Module::Render::DirectX12::DirectX12::Render()
{
	UpdatePipeline();

	ID3D12CommandList* ppCommandLists[] = { commandList };

	commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	TRYFUNC(commandQueue->Signal(fence[frameIndex], fenceValue[frameIndex]));

	TRYFUNC(swapChain->Present(0, 0));

	return true;
}

bool Module::Render::DirectX12::DirectX12::Cleanup()
{
	CloseHandle(fenceEvent);
	WaitForPreviousFrame();

	BOOL fs = false;
	if (swapChain->GetFullscreenState(&fs, nullptr))
		swapChain->SetFullscreenState(false, nullptr);

	SAFE_RELEASE(device);
	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(commandQueue);
	SAFE_RELEASE(rtvDescriptorHeap);
	SAFE_RELEASE(commandList);

	SAFE_RELEASE(pipelineStateObject);
	SAFE_RELEASE(rootSignature);
	SAFE_RELEASE(vertexBuffer);

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
