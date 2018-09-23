#include "Modules/Render/DirectX/Dx12Factory.h"

#include "Engine.h"
#include <d3dcompiler.h>
#include "Modules/Render/DirectX/DX12Helper.h"
#include "Core/CoreType/String.h"
#include "Core/CoreType/Vertex.h"
#include "Macros.h"

bool Module::Render::DirectX12::Dx12Factory::InitFactory()
{
	TRYFUNC(CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)));

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeDevice(ID3D12Device** _device)
{
	Core::CoreType::Container::Vector<IDXGIAdapter1*> compatible_adapters = GetCompatibleAdaptersList();

	if (compatible_adapters.Size() == 0)
		return false;

	TRYFUNC(D3D12CreateDevice(compatible_adapters[0], D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device)));

	*_device = device;

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeCommandQueue(ID3D12CommandQueue** _command_queue)
{
	D3D12_COMMAND_QUEUE_DESC command_queue_desc = {};
	command_queue_desc.Type                     = D3D12_COMMAND_LIST_TYPE_DIRECT;
	command_queue_desc.Flags                    = D3D12_COMMAND_QUEUE_FLAG_NONE;

	TRYFUNC(device->CreateCommandQueue(&command_queue_desc, IID_PPV_ARGS(_command_queue)));

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeSwapChain(ID3D12CommandQueue* _command_queue, const UINT _frame_buffer_count, HWND _window, const UINT _width, const UINT _height, const BOOL _fullscreen, IDXGISwapChain3** _swap_chain)
{
	DXGI_SAMPLE_DESC sample_desc;
	sample_desc.Count   = 1;
	sample_desc.Quality = 0;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreen_desc = {};
	fullscreen_desc.Windowed                        = !_fullscreen;

	DXGI_SWAP_CHAIN_DESC1 swap_chain_descriptor = {};
	swap_chain_descriptor.BufferCount           = _frame_buffer_count;
	swap_chain_descriptor.Width                 = _width;
	swap_chain_descriptor.Height                = _height;
	swap_chain_descriptor.Format                = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_descriptor.BufferUsage           = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_descriptor.SwapEffect            = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swap_chain_descriptor.SampleDesc            = sample_desc;

	IDXGISwapChain1* swap_chain = nullptr;

	TRYFUNC(dxgiFactory->CreateSwapChainForHwnd(_command_queue, _window, &swap_chain_descriptor, &fullscreen_desc, nullptr, &swap_chain));
	*_swap_chain = static_cast<IDXGISwapChain3*>(swap_chain);

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeRenderTargetView(const UINT _frame_buffer_count, IDXGISwapChain3* _swap_chain, ID3D12DescriptorHeap** _rtv_descriptor_heap, UINT* _rtv_descriptor_size, ID3D12Resource** _render_targets)
{
	D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc;
	rtv_heap_desc.NumDescriptors = _frame_buffer_count;
	rtv_heap_desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtv_heap_desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtv_heap_desc.NodeMask       = 0;

	TRYFUNC(device->CreateDescriptorHeap(&rtv_heap_desc, IID_PPV_ARGS(_rtv_descriptor_heap)));

	*_rtv_descriptor_size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_handle((*_rtv_descriptor_heap)->GetCPUDescriptorHandleForHeapStart());

	for (unsigned int i = 0; i < _frame_buffer_count; i++)
	{
		TRYFUNC(_swap_chain->GetBuffer(i, IID_PPV_ARGS(&_render_targets[i])));

		device->CreateRenderTargetView(_render_targets[i], nullptr, rtv_handle);

		rtv_handle.Offset(1, *_rtv_descriptor_size);
	}

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeCommandAllocator(const UINT _frame_buffer_count, ID3D12CommandAllocator** _command_allocator)
{
	for (unsigned int i = 0; i < _frame_buffer_count; i++)
	{
		TRYFUNC(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_command_allocator[i])));
	}

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeCommandList(ID3D12CommandAllocator* _command_allocator, ID3D12GraphicsCommandList** _command_list)
{
	TRYFUNC(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _command_allocator, nullptr, IID_PPV_ARGS(_command_list)));

	(*_command_list)->Close();

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeFence(const UINT _frame_buffer_count, ID3D12Fence** _fence, UINT64* _fence_value, HANDLE* _fence_event)
{
	for (unsigned int i = 0; i < _frame_buffer_count; i++)
	{
		TRYFUNC(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence[i])));
		_fence_value[i] = 0;
	}

	*_fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeRootSignature(ID3D12RootSignature** _root_signature)
{
	D3D12_ROOT_DESCRIPTOR root_cbv_descriptor;
	root_cbv_descriptor.RegisterSpace  = 0;
	root_cbv_descriptor.ShaderRegister = 0;

	D3D12_ROOT_PARAMETER root_parameter;
	root_parameter.ParameterType    = D3D12_ROOT_PARAMETER_TYPE_CBV;
	root_parameter.Descriptor       = root_cbv_descriptor;
	root_parameter.ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	D3D12_ROOT_PARAMETER parameters[] = {root_parameter};

	CD3DX12_ROOT_SIGNATURE_DESC root_signature_desc;
	root_signature_desc.Init(_countof(parameters), parameters, 0, nullptr,
	                         D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
	                         D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
	                         D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
	                         D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
	                         D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS);

	ID3DBlob* serialized_root_signature = nullptr;
	D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &serialized_root_signature, nullptr);

	TRYFUNC(device->CreateRootSignature(0, serialized_root_signature->GetBufferPointer(), serialized_root_signature->GetBufferSize(), IID_PPV_ARGS(_root_signature)));

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeVertexShader(const LPCWSTR _path, D3D12_SHADER_BYTECODE* _shader_bytecode)
{
	ID3DBlob* vertex_shader;
	ID3DBlob* error_buff;
	hr = D3DCompileFromFile(_path, nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertex_shader, &error_buff);
	CHECK_BLOB(error_buff);

	_shader_bytecode->BytecodeLength  = vertex_shader->GetBufferSize();
	_shader_bytecode->pShaderBytecode = vertex_shader->GetBufferPointer();

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakePixelShader(const LPCWSTR _path, D3D12_SHADER_BYTECODE* _shader_bytecode)
{
	ID3DBlob* pixel_shader;
	ID3DBlob* error_buff;
	hr = D3DCompileFromFile(_path, nullptr, nullptr, "main", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixel_shader, &error_buff);
	CHECK_BLOB(error_buff);

	_shader_bytecode->BytecodeLength  = pixel_shader->GetBufferSize();
	_shader_bytecode->pShaderBytecode = pixel_shader->GetBufferPointer();

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeDepthStencilBuffer(ID3D12DescriptorHeap** _descriptor, ID3D12Resource** _buffer, const UINT _width, const UINT _height)
{
	D3D12_DESCRIPTOR_HEAP_DESC heap_desc = {};
	heap_desc.NumDescriptors             = 1;
	heap_desc.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	heap_desc.Flags                      = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	TRYFUNC(device->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(_descriptor)));

	D3D12_RESOURCE_DESC depth_stencil_descriptor = {};
	depth_stencil_descriptor.Dimension           = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depth_stencil_descriptor.Alignment           = 0;
	depth_stencil_descriptor.Width               = _width;
	depth_stencil_descriptor.Height              = _height;
	depth_stencil_descriptor.DepthOrArraySize    = 1;
	depth_stencil_descriptor.Format              = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_stencil_descriptor.SampleDesc.Count    = 1;
	depth_stencil_descriptor.SampleDesc.Quality  = 0;
	depth_stencil_descriptor.Layout              = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depth_stencil_descriptor.Flags               = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE depth_optimized_clear_value;
	depth_optimized_clear_value.Format               = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_optimized_clear_value.DepthStencil.Depth   = 1.0f;
	depth_optimized_clear_value.DepthStencil.Stencil = 0;

	CD3DX12_HEAP_PROPERTIES heap_properties(D3D12_HEAP_TYPE_DEFAULT);

	device->CreateCommittedResource(&heap_properties, D3D12_HEAP_FLAG_NONE, &depth_stencil_descriptor, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depth_optimized_clear_value, IID_PPV_ARGS(_buffer));
	(*_descriptor)->SetName(L"Depth/Stencil Resource Heap");
	(*_buffer)->SetName(L"Depth/Stencil Texture");

	device->CreateDepthStencilView(*_buffer, nullptr, (*_descriptor)->GetCPUDescriptorHandleForHeapStart());

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakePipelineStateObject(ID3D12RootSignature* _root_signature, D3D12_SHADER_BYTECODE* _vertex_shader_bytecode, D3D12_SHADER_BYTECODE* _pixel_shader_bytecode, ID3D12PipelineState** _pipeline_state_object)
{
	D3D12_INPUT_ELEMENT_DESC input_layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
	};

	D3D12_INPUT_LAYOUT_DESC input_layout_desc;
	input_layout_desc.NumElements        = sizeof input_layout / sizeof(D3D12_INPUT_ELEMENT_DESC);
	input_layout_desc.pInputElementDescs = input_layout;

	DXGI_SAMPLE_DESC sample_desc;
	sample_desc.Count   = 1;
	sample_desc.Quality = 0;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_desc = {};
	pso_desc.InputLayout                        = input_layout_desc;
	pso_desc.pRootSignature                     = _root_signature;
	pso_desc.VS                                 = *_vertex_shader_bytecode;
	pso_desc.PS                                 = *_pixel_shader_bytecode;
	pso_desc.PrimitiveTopologyType              = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	pso_desc.RTVFormats[0]                      = DXGI_FORMAT_R8G8B8A8_UNORM;
	pso_desc.SampleDesc                         = sample_desc;
	pso_desc.SampleMask                         = 0xffffffff;
	pso_desc.RasterizerState                    = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	pso_desc.BlendState                         = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	pso_desc.NumRenderTargets                   = 1;
	pso_desc.DepthStencilState                  = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	pso_desc.DSVFormat                          = DXGI_FORMAT_D24_UNORM_S8_UINT;

	TRYFUNC(device->CreateGraphicsPipelineState(&pso_desc, IID_PPV_ARGS(_pipeline_state_object)));

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::CreateVertexBuffer(Dx12CommandExecutionPack _pack, const Core::CoreType::String _name, Core::CoreType::Vertex* _vertices_array, const unsigned int _vertices_count, ID3D12GraphicsCommandList* _command_list, D3D12_VERTEX_BUFFER_VIEW** _vertex_buffer_view)
{
	TRYFUNC(_command_list->Reset(_pack.commandAllocator, _pack.pipelineState));

	Core::CoreType::Vertex* vertex_list = new Core::CoreType::Vertex[_vertices_count];

	for (unsigned int i = 0; i < _vertices_count; ++i)
		vertex_list[i]  = _vertices_array[i];

	const int buffer_size = _vertices_count * sizeof(Core::CoreType::Vertex);

	CD3DX12_HEAP_PROPERTIES default_heap_properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_HEAP_PROPERTIES upload_heap_properties  = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC buffer_size_desc          = CD3DX12_RESOURCE_DESC::Buffer(buffer_size);

	ID3D12Resource* vertex_buffer = nullptr;
	device->CreateCommittedResource(&default_heap_properties, D3D12_HEAP_FLAG_NONE, &buffer_size_desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&vertex_buffer));
	vertex_buffer->SetName((_name + S(" - Vertex Buffer")).ToWideString().CStr());

	ID3D12Resource* vertex_buffer_upload_heap;
	device->CreateCommittedResource(&upload_heap_properties, D3D12_HEAP_FLAG_NONE, &buffer_size_desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertex_buffer_upload_heap));
	vertex_buffer_upload_heap->SetName((_name + S(" - Vertex Upload")).ToWideString().CStr());

	D3D12_SUBRESOURCE_DATA vertex_data;
	vertex_data.pData      = reinterpret_cast<BYTE*>(vertex_list);
	vertex_data.RowPitch   = buffer_size;
	vertex_data.SlicePitch = buffer_size;

	UpdateSubresources(_command_list, vertex_buffer, vertex_buffer_upload_heap, 0, 0, 1, &vertex_data);

	CD3DX12_RESOURCE_BARRIER transition_barrier = CD3DX12_RESOURCE_BARRIER::Transition(vertex_buffer, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	_command_list->ResourceBarrier(1, &transition_barrier);

	_command_list->Close();
	ID3D12CommandList* pp_command_lists[] = {_command_list};
	_pack.commandQueue->ExecuteCommandLists(_countof(pp_command_lists), pp_command_lists);

	HANDLE fence_event = nullptr;

	(*_pack.fenceValue)++;
	TRYFUNC(_pack.commandQueue->Signal(_pack.fence, *_pack.fenceValue));
	_pack.fence->SetEventOnCompletion(*_pack.fenceValue, fence_event);
	WaitForSingleObject(fence_event, INFINITE);

	*_vertex_buffer_view                   = new D3D12_VERTEX_BUFFER_VIEW;
	(*_vertex_buffer_view)->BufferLocation = vertex_buffer->GetGPUVirtualAddress();
	(*_vertex_buffer_view)->StrideInBytes  = sizeof(Core::CoreType::Vertex);
	(*_vertex_buffer_view)->SizeInBytes    = buffer_size;

	delete[] vertex_list;

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::CreateIndexBuffer(Dx12CommandExecutionPack _pack, const Core::CoreType::String _name, unsigned int* _indexes_array, const unsigned int _indexes_count, ID3D12GraphicsCommandList* _command_list, D3D12_INDEX_BUFFER_VIEW** _index_buffer_view)
{
	TRYFUNC(_command_list->Reset(_pack.commandAllocator, _pack.pipelineState));

	unsigned int* index_list = new unsigned int[_indexes_count];

	for (unsigned int i = 0; i < _indexes_count; ++i)
		index_list[i]   = _indexes_array[i];

	const int buffer_size = _indexes_count * sizeof(unsigned int);

	CD3DX12_HEAP_PROPERTIES default_heap_properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_HEAP_PROPERTIES upload_heap_properties  = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC buffer_size_desc          = CD3DX12_RESOURCE_DESC::Buffer(buffer_size);

	ID3D12Resource* index_buffer = nullptr;
	device->CreateCommittedResource(&default_heap_properties, D3D12_HEAP_FLAG_NONE, &buffer_size_desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&index_buffer));
	index_buffer->SetName((_name + S(" - Index Buffer")).ToWideString().CStr());

	ID3D12Resource* index_buffer_upload_heap;
	device->CreateCommittedResource(&upload_heap_properties, D3D12_HEAP_FLAG_NONE, &buffer_size_desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&index_buffer_upload_heap));
	index_buffer_upload_heap->SetName((_name + S(" - Index Upload")).ToWideString().CStr());

	D3D12_SUBRESOURCE_DATA index_data;
	index_data.pData      = reinterpret_cast<BYTE*>(index_list);
	index_data.RowPitch   = buffer_size;
	index_data.SlicePitch = buffer_size;

	UpdateSubresources(_command_list, index_buffer, index_buffer_upload_heap, 0, 0, 1, &index_data);

	CD3DX12_RESOURCE_BARRIER transition_barrier = CD3DX12_RESOURCE_BARRIER::Transition(index_buffer, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	_command_list->ResourceBarrier(1, &transition_barrier);

	_command_list->Close();
	ID3D12CommandList* pp_command_lists[] = {_command_list};
	_pack.commandQueue->ExecuteCommandLists(_countof(pp_command_lists), pp_command_lists);

	HANDLE fence_event = nullptr;

	(*_pack.fenceValue)++;
	TRYFUNC(_pack.commandQueue->Signal(_pack.fence, *_pack.fenceValue));
	_pack.fence->SetEventOnCompletion(*_pack.fenceValue, fence_event);
	WaitForSingleObject(fence_event, INFINITE);

	*_index_buffer_view                   = new D3D12_INDEX_BUFFER_VIEW;
	(*_index_buffer_view)->BufferLocation = index_buffer->GetGPUVirtualAddress();
	(*_index_buffer_view)->Format         = DXGI_FORMAT_R32_UINT;
	(*_index_buffer_view)->SizeInBytes    = buffer_size;

	delete[] index_list;

	return true;
}

Core::CoreType::Container::Vector<IDXGIAdapter1*> Module::Render::DirectX12::Dx12Factory::GetAdaptersList() const
{
	Core::CoreType::Container::Vector<IDXGIAdapter1*> adapters;
	IDXGIAdapter1* adapter;
	int adapter_index = 0;

	while (dxgiFactory->EnumAdapters1(adapter_index, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		adapters.PushBack(adapter);
		++adapter_index;
	}

	return adapters;
}

Core::CoreType::Container::Vector<IDXGIAdapter1*> Module::Render::DirectX12::Dx12Factory::GetCompatibleAdaptersList() const
{
	Core::CoreType::Container::Vector<IDXGIAdapter1*> adapters = GetAdaptersList();
	Core::CoreType::Container::Vector<IDXGIAdapter1*> compatible_adapters;

	for (IDXGIAdapter1* adapter : adapters)
	{
		const HRESULT adapter_compatible = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr);
		if (SUCCEEDED(adapter_compatible))
			compatible_adapters.PushBack(adapter);
	}

	return compatible_adapters;
}

Core::CoreType::Container::Vector<IDXGIOutput*> Module::Render::DirectX12::Dx12Factory::GetOutputList(IDXGIAdapter1* _adapter)
{
	Core::CoreType::Container::Vector<IDXGIOutput*> outputs;
	IDXGIOutput* output;
	int output_index = 0;

	while (_adapter->EnumOutputs(output_index, &output) != DXGI_ERROR_NOT_FOUND)
	{
		outputs.PushBack(output);
		++output_index;
	}

	return outputs;
}

void Module::Render::DirectX12::Dx12Factory::LogAdapters(Core::CoreType::Container::Vector<IDXGIAdapter1*> _adapters)
{
	DXGI_ADAPTER_DESC1 desc;
	for (IDXGIAdapter1* adapter : _adapters)
	{
		adapter->GetDesc1(&desc);
		LOG(S("Adapter : ") + WS(desc.Description).ToCharString(), LOG_VERBOSE);
		LogOutputs(GetOutputList(adapter));
	}
}

void Module::Render::DirectX12::Dx12Factory::LogOutputs(Core::CoreType::Container::Vector<IDXGIOutput*> _outputs)
{
	DXGI_OUTPUT_DESC desc;
	for (IDXGIOutput* output : _outputs)
	{
		output->GetDesc(&desc);
		LOG(S("Output : ") + WS(desc.DeviceName).ToCharString(), LOG_VERBOSE);
	}
}
