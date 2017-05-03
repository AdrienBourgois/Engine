#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>

#include "Macros.h"
#include "Core/Interface/IRender.h"
#include "Modules/Display/Window.h"

#include "Modules/Render/DirectX/Dx12Factory.h"
#include "Core/CoreType/Vertex.h"

#define FRAME_BUFFER_COUNT 3

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

namespace Module
{
	namespace Render
	{
		namespace DirectX12
		{
			class DirectX12 : public Core::Interface::IRender
			{
			public:

				explicit DirectX12() = default;
				~DirectX12() = default;

				bool Initialize() override;
				bool CreatePipeline() override;
				bool Render() override;
				bool Cleanup() override;

				bool MakeVertexBuffer(int _id, const Core::CoreType::Vertex* _vertex, UINT _size, LPCWSTR _name);

			private:
				bool UpdatePipeline();
				bool WaitForPreviousFrame();
				bool PreparePreRenderCommandList();
				bool PreparePostRenderCommandList();
				bool PrepareObjectCommandList(int _objectCommandListNumber);

				HRESULT hr = 0;

				Dx12Factory* factory = nullptr;

				//Reference Objects
				Module::Display::Window* window_reference = nullptr;
				HWND* window_handle_reference = nullptr;

				//Init Objects
				DXGI_SAMPLE_DESC sampleDesc = {};

				D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};

				ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
				UINT rtvDescriptorSize = 0;

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

				//Per-frame used Objects
				IDXGISwapChain3* swapChain = nullptr;

				ID3D12Resource* renderTargets[FRAME_BUFFER_COUNT];

				ID3D12CommandQueue* commandQueue = nullptr;
				ID3D12CommandAllocator* commandAllocator[FRAME_BUFFER_COUNT];
				ID3D12GraphicsCommandList* preRenderCommandList = nullptr;
				ID3D12GraphicsCommandList* postRenderCommandList = nullptr;
				ID3D12GraphicsCommandList* resourcesRenderCommandList = nullptr;

				std::unordered_map<int, ID3D12GraphicsCommandList*> objectCommandLists;
				std::unordered_map<int, D3D12_VERTEX_BUFFER_VIEW*> vertexBufferViews;

				int frameIndex = 0;
			};
		}
	}
}
