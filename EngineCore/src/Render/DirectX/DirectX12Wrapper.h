#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>

#include "Engine.h"
#include "IModule.h"
#include "Display/Window.h"

#define FRAME_BUFFER_COUNT 3

#define CHECK() if(FAILED(hr)) { ENGINE->Stop(); return; }

#define CHECK_BLOB(blob) if(FAILED(hr)) { OutputDebugStringA((char*)errorBuff->GetBufferPointer()); return; }

#define TRYFUNC(command) hr = command;\
	if(FAILED(hr)) { MessageBox(nullptr, L"Error", L"Error", MB_OK | MB_ICONERROR); ENGINE->Stop(); return; }

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) \
   if(x != NULL)        \
   {                    \
	  x->Release();     \
	  x = NULL;         \
   }
#endif

#ifndef SAFE_ARRAY_DELETE
#define SAFE_ARRAY_DELETE(x) \
   if(x != NULL)             \
   {                         \
	  delete[] x;            \
	  x = NULL;              \
   }
#endif

class DirectX12Wrapper : public IModule
{
public:

	DECLARE_MODULE(S("DirectX12Wrapper"))

	explicit DirectX12Wrapper();
	~DirectX12Wrapper();

	void UpdatePipeline();
	void Render();
	void WaitForPreviousFrame();

	void Cleanup();

private:

	void MakeDevice();
	void MakeCommandQueue();
	void MakeSwapChain();
	void MakeDescriptorHeap();
	void MakeCommandList();
	void MakeFence();
	void MakeRootDescriptor();
	void MakeVertexShader();
	void MakePixelShader();
	void MakePipelineStateObject();
	void MakeVertexBuffer();

	HRESULT hr = 0;

//Reference Objects
	Display::Window* window_reference = nullptr;
	HWND* window_handle_reference = nullptr;

//Init Objects
	IDXGIFactory4* dxgiFactory = nullptr;

	DXGI_SAMPLE_DESC sampleDesc = {};

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};

	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	int rtvDescriptorSize = 0;

//Handle Objects
	ID3D12Device* device = nullptr;

	ID3D12PipelineState* pipelineStateObject = nullptr;

	ID3D12RootSignature* rootSignature = nullptr;

	ID3D12Fence* fence[FRAME_BUFFER_COUNT];
	HANDLE fenceEvent = nullptr;
	UINT64 fenceValue[FRAME_BUFFER_COUNT];

	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;

	D3D12_SHADER_BYTECODE vertexShaderBytecode = {};
	D3D12_SHADER_BYTECODE pixelShaderBytecode  = {};

	ID3D12Resource* vertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

//Per-frame used Objects
	IDXGISwapChain3* swapChain = nullptr;

	ID3D12Resource* renderTargets[FRAME_BUFFER_COUNT];

	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12CommandAllocator* commandAllocator[FRAME_BUFFER_COUNT];
	ID3D12GraphicsCommandList* commandList = nullptr;

	int frameIndex = 0;
};