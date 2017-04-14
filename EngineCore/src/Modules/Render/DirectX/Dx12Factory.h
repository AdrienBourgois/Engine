#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>

/**
 * \brief Return false if function failed
 * \param function Function to test
 */
#define TRYFUNC(function) hr = 0;\
						  hr = function;\
						  if(FAILED(hr)) return false;

/**
 * \brief Return false if Blob has error
 * \param blob ID3DBlob to test
 */
#define CHECK_BLOB(blob) if(FAILED(hr))\
						 { OutputDebugStringA((char*)blob->GetBufferPointer()); return false; }

namespace Module
{
	namespace Render
	{
		namespace DirectX12
		{
			/**
			 * \brief Factory to create Dx12 elements
			 */
			class Dx12Factory
			{
			public:
				/**
				 * \brief Default constructor
				 */
				Dx12Factory() = default;
				/**
				 * \brief Default destructor
				 */
				~Dx12Factory() = default;

				bool CreateObjectCommandList(ID3D12CommandAllocator* _command_allocator, ID3D12GraphicsCommandList** _command_list);
				/**
				 * \brief Initialize DXGIFactory
				 * \return Is function success
				 */
				bool InitFactory();
				/**
				 * \brief Search adapter and create device
				 * \param[out] _device Pointer to ID3D12Device
				 * \return Is function success
				 * \note Must be called after Dx12Factory::InitFactory
				 */
				bool MakeDevice(ID3D12Device** _device);
				/**
				 * \brief Create Command queue
				 * \param[out] _commandQueue Pointer to ID3D12CommandQueue
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeCommandQueue(ID3D12CommandQueue** _commandQueue);
				/**
				 * \brief Create SwapChain
				 * \param _device A Direct Command Queue
				 * \param _frame_buffer_count Count of frames buffer used
				 * \param _window Window reference
				 * \param _width Width of render
				 * \param _height Height of render
				 * \param _fullscreen Is window fullscreen
				 * \param _commandQueue Command queue to use with SwapChain
				 * \param[out] _swap_chain Pointer to IDXGISwapChain3
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeSwapChain(IUnknown* _device ,UINT _frame_buffer_count, HWND _window, UINT _width, UINT _height, BOOL _fullscreen, ID3D12CommandQueue* _commandQueue, IDXGISwapChain3** _swap_chain);
				/**
				 * \brief Create Descriptor heap and renders targets
				 * \param _frame_buffer_count Count of frames buffer used
				 * \param _swap_chain SwapChain to use
				 * \param[out] _rtv_descriptor_heap Pointer to ID3D12DescriptorHeap
				 * \param[out] _rtv_descriptor_size Pointer to UINT
				 * \param[out] _render_targets Pointer to an array of ID3D12Resource
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeDescriptorHeap(UINT _frame_buffer_count, IDXGISwapChain3* _swap_chain, ID3D12DescriptorHeap** _rtv_descriptor_heap, UINT* _rtv_descriptor_size, ID3D12Resource** _render_targets);
				/**
				 * \brief Create Command allocators
				 * \param _frame_buffer_count Count of frames buffer used
				 * \param[out] _command_allocator Pointer to an array of ID3D12CommandAllocator
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeCommandAllocator(UINT _frame_buffer_count, ID3D12CommandAllocator** _command_allocator);
				/**
				 * \brief Create Command list
				 * \param _command_allocator Pointer to ID3D12CommandAllocator
				 * \param[out] _command_list Pointer to ID3D12GraphicsCommandList
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeCommandList(ID3D12CommandAllocator* _command_allocator, ID3D12GraphicsCommandList** _command_list);
				/**
				 * \brief Create fences and event
				 * \param _frame_buffer_count Count of frames buffer used
				 * \param[out] _fence Pointer to an array of ID3D12Fence
				 * \param[out] _fence_value Pointer to an array of UINT64
				 * \param[out] fence_event Pointer to an HANDLE
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeFence(UINT _frame_buffer_count, ID3D12Fence** _fence, UINT64* _fence_value, HANDLE* fence_event);
				/**
				 * \brief Create Root Signature
				 * \param[out] _root_signature Pointer to ID3D12RootSignature
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeRootSignature(ID3D12RootSignature** _root_signature);
				/**
				 * \brief Compile a Vertex shader
				 * \param _path Path to shader file
				 * \param[out] _shader_bytecode Pointer to D3D12_SHADER_BYTECODE
				 * \return Is function success
				 */
				bool MakeVertexShader(LPCWSTR _path, D3D12_SHADER_BYTECODE* _shader_bytecode);
				/**
				 * \brief Compile a Pixel shader
				 * \param _path Path to shader file
				 * \param[out] _shader_bytecode Pointer to D3D12_SHADER_BYTECODE
				 * \return Is function success
				 */
				bool MakePixelShader(LPCWSTR _path, D3D12_SHADER_BYTECODE* _shader_bytecode);
				/**
				 * \brief Create PSO
				 * \param _root_signature Root Signature to use
				 * \param _vertex_shader_bytecode Vertex Shader to use
				 * \param _pixel_shader_bytecode Pixel Shader to use
				 * \param[out] _pipeline_state_object Pointer to ID3D12PipelineState
				 * \return Is function success
				 */
				bool MakePipelineStateObject(ID3D12RootSignature* _root_signature, D3D12_SHADER_BYTECODE* _vertex_shader_bytecode, D3D12_SHADER_BYTECODE* _pixel_shader_bytecode, ID3D12PipelineState** _pipeline_state_object);
			private:
				IDXGIFactory4* dxgiFactory = nullptr;
				ID3D12Device* device = nullptr;

				HRESULT hr = 0;
			};
		}
	}
}
