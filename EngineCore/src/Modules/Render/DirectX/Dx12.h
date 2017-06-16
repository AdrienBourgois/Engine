#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>

#include "Macros.h"
#include "Core/Interface/IRender.h"
#include "Modules/Display/Window.h"

#include "Modules/Render/DirectX/Dx12Factory.h"
#include "Modules/Render/DirectX/Objects/Dx12GraphicObject.h"
#include "Maths/Mat4.h"
#include "Core/CoreType/Transform.h"

/**
 * \brief Count of frame for memory management
 */
#define FRAME_BUFFER_COUNT 3

#ifndef SAFE_RELEASE
/**
 * \brief Macro to safe release Dx12 objects
 * \param x Object to release
 */
#define SAFE_RELEASE(x) \
   if(x != NULL)        \
   {                    \
	  x->Release();     \
	  x = NULL;         \
   }
#endif

#ifndef SAFE_ARRAY_DELETE
/**
 * \brief Macro to safely delete an array
 * \param x Array to delete
 */
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
		/**
		 * \brief Direct X 12 related classes
		 */
		namespace DirectX12
		{
			/**
			 * \brief DirectX 12 renderer
			 */
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
				bool CreateBuffers(unsigned int _id, Core::CoreType::String _name, Core::CoreType::Transform* _transform, Core::CoreType::Vertex* _vertices_array, unsigned int _vertices_count, unsigned int* _indexs_array = nullptr, unsigned int _indexs_count = 0) override;
				void SetCameraViewMatrix(Math::Mat4 _camera_view) override;
				void SetCameraProjectionMatrix(Math::Mat4 _camera_projection) override;
				bool Render() override;
				bool Cleanup() override;

			private:
				/**
				 * \brief Make pre render operations
				 * \return Is function success
				 */
				bool PreRender();
				/**
				 * \brief Make post render operations
				 * \return Is function success
				 */
				bool PostRender() const;

				/**
				 * \brief Update the pipeline
				 * \return Is function success
				 */
				bool UpdatePipeline() const;
				/**
				 * \brief Block until the GPU had finished rendering previous frame
				 * \return Is function success
				 */
				bool WaitForPreviousFrame();
				/**
				 * \brief Prepare the pre render command list
				 * \return Is function success
				 */
				bool PreparePreRenderCommandList();
				/**
				 * \brief Prepare the post render command list
				 * \return Is function success
				 */
				bool PreparePostRenderCommandList();
				/**
				 * \brief Prepare command lists of object
				 * \param _graphic_object Object to prepare
				 * \return Is function success
				 */
				bool PrepareObjectCommandList(Objects::Dx12GraphicObject* _graphic_object);

				/**
				 * \brief Handle result of Dx12 functions
				 */
				HRESULT hr = 0;

				/**
				 * \brief Pointer to the Dx12 objects factory
				 */
				Dx12Factory* factory = nullptr;

				/**
				 * \brief Store reference to the window module
				 */
				Display::Window* windowReference = nullptr;
				/**
				 * \brief Store reference to the window handler
				 */
				HWND* windowHandleReference = nullptr;

				/**
				 * \brief Descriptor of the input layout
				 */
				D3D12_INPUT_LAYOUT_DESC inputLayoutDescriptor = {};

				/**
				 * \brief Descriptor for the render target heap
				 */
				ID3D12DescriptorHeap* renderTargetDescriptorHeap = nullptr;
				/**
				 * \brief Size of the render target descriptor
				 */
				UINT renderTargetDescriptorSize = 0;

				/**
				 * \brief Dx12 device
				 */
				ID3D12Device* device = nullptr;

				/**
				 * \brief Current PSO used
				 */
				ID3D12PipelineState* pipelineStateObject = nullptr;

				/**
				 * \brief Current root signature used
				 */
				ID3D12RootSignature* rootSignature = nullptr;

				/**
				 * \brief Store fences
				 */
				ID3D12Fence* fence[FRAME_BUFFER_COUNT];
				/**
				 * \brief Current fence event of current frame
				 */
				HANDLE fenceEvent = nullptr;
				/**
				 * \brief Store fences values
				 */
				UINT64 fenceValue[FRAME_BUFFER_COUNT];

				/**
				 * \brief Viewport
				 */
				D3D12_VIEWPORT viewport;
				/**
				 * \brief Scissor rectangle
				 */
				D3D12_RECT scissorRect;

				/**
				 * \brief Bytecode of current vertex shader
				 */
				D3D12_SHADER_BYTECODE vertexShaderBytecode = {};
				/**
				 * \brief Bytecode of current pixel shader
				 */
				D3D12_SHADER_BYTECODE pixelShaderBytecode  = {};

				/**
				 * \brief Swap chain
				 */
				IDXGISwapChain3* swapChain = nullptr;

				/**
				 * \brief Store render target of each frame buffer
				 */
				ID3D12Resource* renderTargets[FRAME_BUFFER_COUNT];

				/**
				 * \brief Command queue
				 */
				ID3D12CommandQueue* commandQueue = nullptr;
				/**
				 * \brief Commands allocators of each frame buffer
				 */
				ID3D12CommandAllocator* commandAllocator[FRAME_BUFFER_COUNT];
				/**
				 * \brief Pre render command list
				 */
				ID3D12GraphicsCommandList* preRenderCommandList = nullptr;
				/**
				 * \brief Post render command list
				 */
				ID3D12GraphicsCommandList* postRenderCommandList = nullptr;

				/**
				 * \brief Depth stencil buffer
				 */
				ID3D12Resource* depthStencilBuffer = nullptr;
				/**
				 * \brief Depth stencil buffer descriptor
				 */
				ID3D12DescriptorHeap* depthStencilDescriptorHeap = nullptr;

				/**
				 * \brief Store graphics objects with id's
				 */
				std::unordered_map<int, Objects::Dx12GraphicObject*> graphicsObjects;

				/**
				 * \brief Current frame buffer index
				 */
				int frameIndex = 0;

				/**
				 * \brief Current project matrix
				 */
				Math::Mat4 cameraProjectionMatrix;
				/**
				 * \brief Current camera view matrix
				 */
				Math::Mat4 cameraViewMatrix;
			};
		}
	}
}
