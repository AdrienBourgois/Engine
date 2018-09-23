#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include "DX12Helper.h"
#include "Modules/Render/DirectX/Objects/Dx12ConstantBuffer.h"
#include "Core/CoreType/Container/Vector.h"
#include "Core/CoreType/String.h"

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
						 { OutputDebugStringA((char*)(blob)->GetBufferPointer()); return false; }

namespace Core
{
	namespace CoreType
	{
		class Vertex;
	}
}

namespace Module
{
	namespace Render
	{
		namespace DirectX12
		{
			/**
			 * \brief Pack of pointer to element to execute command list functions
			 */
			struct Dx12CommandExecutionPack
			{
				/**
				 * \brief Pointer to the PSO
				 */
				ID3D12PipelineState* pipelineState;
				/**
				 * \brief Pointer to the command allocator
				 */
				ID3D12CommandAllocator* commandAllocator;
				/**
				 * \brief Pointer to the command queue
				 */
				ID3D12CommandQueue* commandQueue;
				/**
				 * \brief Pointer to the current fence
				 */
				ID3D12Fence* fence;
				/**
				 * \brief Pointer to the current fence value
				 */
				UINT64* fenceValue;
			};

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

				/**
				 * \brief Initialize DXGIFactory
				 * \return Is function success
				 */
				bool InitFactory();

				/*********************************** Create Objects ***********************************/

				/**
				 * \brief Search adapter and create device
				 * \param[out] _device Pointer to ID3D12Device
				 * \return Is function success
				 * \note Must be called after Dx12Factory::InitFactory
				 */
				bool MakeDevice(ID3D12Device** _device);
				/**
				 * \brief Create Command queue
				 * \param[out] _command_queue Pointer to ID3D12CommandQueue
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeCommandQueue(ID3D12CommandQueue** _command_queue);
				/**
				 * \brief Create SwapChain
				 * \param _command_queue A Direct Command Queue
				 * \param _frame_buffer_count Count of frames buffer used
				 * \param _window Window reference
				 * \param _width Width of render
				 * \param _height Height of render
				 * \param _fullscreen Is window fullscreen
				 * \param[out] _swap_chain Pointer to IDXGISwapChain3
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeSwapChain(ID3D12CommandQueue* _command_queue, UINT _frame_buffer_count, HWND _window, UINT _width, UINT _height, BOOL _fullscreen, IDXGISwapChain3** _swap_chain);
				/**
				 * \brief Create Renders target views
				 * \param _frame_buffer_count Count of frames buffer used
				 * \param _swap_chain SwapChain to use
				 * \param[out] _rtv_descriptor_heap Pointer to ID3D12DescriptorHeap
				 * \param[out] _rtv_descriptor_size Pointer to UINT
				 * \param[out] _render_targets Pointer to an array of ID3D12Resource
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeRenderTargetView(UINT _frame_buffer_count, IDXGISwapChain3* _swap_chain, ID3D12DescriptorHeap** _rtv_descriptor_heap, UINT* _rtv_descriptor_size, ID3D12Resource** _render_targets);
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
				 * \param[out] _fence_event Pointer to an HANDLE
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeFence(UINT _frame_buffer_count, ID3D12Fence** _fence, UINT64* _fence_value, HANDLE* _fence_event);
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
				 * \brief Create a Depth/Stencil buffer with the descriptor
				 * \param[out] _descriptor Pointer to a ID3D12DescriptorHeap
				 * \param[out] _buffer Pointer to a ID3D12Resource
				 * \param _width Width of the buffer
				 * \param _height Weight of the buffer
				 * \return Is function success
				 * \note Must be called after Dx12Factory::MakeDevice
				 */
				bool MakeDepthStencilBuffer(ID3D12DescriptorHeap** _descriptor, ID3D12Resource** _buffer, UINT _width, UINT _height);
				/**
				 * \brief Create PSO
				 * \param _root_signature Root Signature to use
				 * \param _vertex_shader_bytecode Vertex Shader to use
				 * \param _pixel_shader_bytecode Pixel Shader to use
				 * \param[out] _pipeline_state_object Pointer to ID3D12PipelineState
				 * \return Is function success
				 */
				bool MakePipelineStateObject(ID3D12RootSignature* _root_signature, D3D12_SHADER_BYTECODE* _vertex_shader_bytecode, D3D12_SHADER_BYTECODE* _pixel_shader_bytecode, ID3D12PipelineState** _pipeline_state_object);

				/*********************************** Create Buffers ***********************************/

				/**
				 * \brief Create a vertex buffer
				 * \param _pack Dx12CommandExecutionPack with objects needed to create buffer
				 * \param _name Name of buffer
				 * \param _vertices_array Array of vertices
				 * \param _vertices_count Size of vertices array
				 * \param _command_list Command list used to create buffer
				 * \param[out] _vertex_buffer_view Pointer to a D3D12_VERTEX_BUFFER_VIEW
				 * \return Is function success
				 */
				bool CreateVertexBuffer(Dx12CommandExecutionPack _pack, Core::CoreType::String _name, Core::CoreType::Vertex* _vertices_array, unsigned int _vertices_count, ID3D12GraphicsCommandList* _command_list, D3D12_VERTEX_BUFFER_VIEW** _vertex_buffer_view);
				/**
				 * \brief Create an index buffer from object
				 * \param _pack Dx12CommandExecutionPack with objects needed to create buffer
				 * \param _name Name of buffer
				 * \param _indexes_array Array of indexes (If vertices are indexed)
				 * \param _indexes_count Size of indexes array
				 * \param _command_list Command list used to create buffer
				 * \param[out] _index_buffer_view Pointer to a D3D12_INDEX_BUFFER_VIEW
				 * \return Is function success
				 */
				bool CreateIndexBuffer(Dx12CommandExecutionPack _pack, Core::CoreType::String _name, unsigned int* _indexes_array, unsigned int _indexes_count, ID3D12GraphicsCommandList* _command_list, D3D12_INDEX_BUFFER_VIEW** _index_buffer_view);
				/**
				 * \brief Create a constant buffer
				 * \tparam T Type of data to pass
				 * \param _data Default data for buffer
				 * \param[out] _constant_buffer Pointer to a Module::Render::DirectX12::Objects::Dx12ConstantBuffer
				 * \return Is function success
				 */
				template <typename T>
				bool CreateConstantBuffer(T* _data, Objects::Dx12ConstantBuffer** _constant_buffer);

			private:

				Core::CoreType::Container::Vector<IDXGIAdapter1*> GetAdaptersList() const;
				Core::CoreType::Container::Vector<IDXGIAdapter1*> GetCompatibleAdaptersList() const;
				static Core::CoreType::Container::Vector<IDXGIOutput*> GetOutputList(IDXGIAdapter1* _adapter);

				static void LogAdapters(Core::CoreType::Container::Vector<IDXGIAdapter1*> _adapters);
				static void LogOutputs(Core::CoreType::Container::Vector<IDXGIOutput*> _outputs);



				/**
				 * \brief Pointer to the DirectX Factory kept to create objects
				 */
				IDXGIFactory4* dxgiFactory = nullptr;
				/**
				 * \brief Pointer to the device kept for DirectX factory
				 */
				ID3D12Device* device = nullptr;

				/**
				 * \brief Store result of DirectX functions
				 */
				HRESULT hr = 0;
			};

			template <typename T>
			bool Dx12Factory::CreateConstantBuffer(T* _data, Objects::Dx12ConstantBuffer** _constant_buffer)
			{
				ID3D12DescriptorHeap* heap_descriptor = nullptr;

				D3D12_DESCRIPTOR_HEAP_DESC heap_desc = {};
				heap_desc.NumDescriptors = 1;
				heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
				heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				TRYFUNC(device->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(&heap_descriptor)));

				ID3D12Resource* constant_buffer_upload_heap = nullptr;

				CD3DX12_HEAP_PROPERTIES upload_heap_properties  = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
				CD3DX12_RESOURCE_DESC resource_descriptor = CD3DX12_RESOURCE_DESC::Buffer(1024 * 64);
				TRYFUNC(device->CreateCommittedResource(&upload_heap_properties, D3D12_HEAP_FLAG_NONE, &resource_descriptor, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&constant_buffer_upload_heap)));
				constant_buffer_upload_heap->SetName(L"Constant Buffer Upload Resource Heap");

				D3D12_CONSTANT_BUFFER_VIEW_DESC constant_buffer_view_desc;
				constant_buffer_view_desc.BufferLocation = constant_buffer_upload_heap->GetGPUVirtualAddress();
				constant_buffer_view_desc.SizeInBytes = sizeof(_data) + 255 & ~255;
				device->CreateConstantBufferView(&constant_buffer_view_desc, heap_descriptor->GetCPUDescriptorHandleForHeapStart());

				*_constant_buffer = new Objects::Dx12ConstantBuffer(heap_descriptor, constant_buffer_upload_heap);

				memcpy((*_constant_buffer)->Map(), &_data, sizeof(_data));

				(*_constant_buffer)->Unmap();

				return true;
			}
		}
	}
}
