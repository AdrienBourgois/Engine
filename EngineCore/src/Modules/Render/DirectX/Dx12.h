#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>

#include "Macros.h"
#include "Core/Interface/IRender.h"
#include "Modules/Display/Window.h"

#include "Modules/Render/DirectX/Dx12Factory.h"
#include "Modules/Render/DirectX/Objects/Dx12GraphicObject.h"
#include "Modules/Render/DirectX/Objects/Dx12RootSignatureDescritor.h"

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
				/**
				 * \brief Default constructor
				 */
				DirectX12() = default;
				/**
				 * \brief Default destructor
				 */
				~DirectX12() = default;

				bool Initialize() override;
				bool CreatePipeline() override;
				bool CreateBuffers(unsigned int _id, Core::CoreType::String _name, Core::CoreType::Vertex* _vertices_array, unsigned int _vertices_count, unsigned int* _indexs_array = nullptr, unsigned int _indexs_count = 0) override;
				bool Render() override;
				bool Cleanup() override;

			private:
				/**
				 * \brief Create a vertex buffer
				 * \param _name Name of buffer
				 * \param _vertices_array Array of vertices
				 * \param _vertices_count Size of vertices array
				 * \param[out] _vertex_buffer_view Pointer to a D3D12_VERTEX_BUFFER_VIEW
				 * \return Is function success
				 */
				bool CreateVertexBuffer(Core::CoreType::String _name, Core::CoreType::Vertex* _vertices_array, unsigned int _vertices_count, ID3D12GraphicsCommandList* _command_list, D3D12_VERTEX_BUFFER_VIEW** _vertex_buffer_view);
				/**
				 * \brief Create an index buffer from object
				 * \param _name Name of buffer
				 * \param _indexs_array Array of indexs (If vertices are indexed)
				 * \param _indexs_count Size of indexs array
				 * \param[out] _index_buffer_view Pointer to a D3D12_INDEX_BUFFER_VIEW
				 * \return Is function success
				 */
				bool CreateIndexBuffer(Core::CoreType::String _name, unsigned int* _indexs_array, unsigned int _indexs_count, ID3D12GraphicsCommandList* _command_list, D3D12_INDEX_BUFFER_VIEW** _index_buffer_view);

				bool UpdatePipeline();
				bool WaitForPreviousFrame();
				bool PreparePreRenderCommandList();
				bool PreparePostRenderCommandList();
				bool PrepareObjectCommandList(Objects::Dx12GraphicObject* _graphic_object);

				HRESULT hr = 0;

				Dx12Factory* factory = nullptr;

				Display::Window* windowReference = nullptr;
				HWND* windowHandleReference = nullptr;

				DXGI_SAMPLE_DESC sampleDescriptor = {};

				D3D12_INPUT_LAYOUT_DESC inputLayoutDescriptor = {};

				ID3D12DescriptorHeap* renderTargetDescriptorHeap = nullptr;
				UINT renderTargetDescriptorSize = 0;

				ID3D12Device* device = nullptr;

				ID3D12PipelineState* pipelineStateObject = nullptr;

				ID3D12RootSignature* rootSignature = nullptr;
				Objects::Dx12RootSignatureDescritor* rootSignatureSerializer = nullptr;

				ID3D12Fence* fence[FRAME_BUFFER_COUNT];
				HANDLE fenceEvent = nullptr;
				UINT64 fenceValue[FRAME_BUFFER_COUNT];

				D3D12_VIEWPORT viewport;
				D3D12_RECT scissorRect;

				D3D12_SHADER_BYTECODE vertexShaderBytecode = {};
				D3D12_SHADER_BYTECODE pixelShaderBytecode  = {};

				IDXGISwapChain3* swapChain = nullptr;

				ID3D12Resource* renderTargets[FRAME_BUFFER_COUNT];

				ID3D12CommandQueue* commandQueue = nullptr;
				ID3D12CommandAllocator* commandAllocator[FRAME_BUFFER_COUNT];
				ID3D12GraphicsCommandList* preRenderCommandList = nullptr;
				ID3D12GraphicsCommandList* postRenderCommandList = nullptr;

				ID3D12Resource* depthStencilBuffer = nullptr;
				ID3D12DescriptorHeap* depthStencilDescriptorHeap = nullptr;

				std::unordered_map<int, Objects::Dx12GraphicObject*> graphicsObjects;

				int frameIndex = 0;
			};
		}
	}
}
