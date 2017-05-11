#include "Modules/Render/DirectX/Dx12Factory.h"

#include <D3Dcompiler.h>
#include "Modules/Render/DirectX/DX12Helper.h"

bool Module::Render::DirectX12::Dx12Factory::InitFactory()
{
	TRYFUNC(CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)));

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeDevice(ID3D12Device** _device)
{
	IDXGIAdapter1* adapter;

	int adapterIndex = 0;
	bool adapterFound = false;

	while (dxgiFactory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			adapterIndex++;

		HRESULT adapter_compatible = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr);
		if (SUCCEEDED(adapter_compatible))
		{
			adapterFound = true;
			break;
		}

		adapterIndex++;
	}

	if (!adapterFound)
		return false;

	TRYFUNC(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(_device)));

	device = *_device;

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeCommandQueue(ID3D12CommandQueue** _commandQueue)
{
	D3D12_COMMAND_QUEUE_DESC command_queue_desc = {};

	TRYFUNC(device->CreateCommandQueue(&command_queue_desc, IID_PPV_ARGS(_commandQueue)));

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeSwapChain(IUnknown* _device, UINT _frame_buffer_count, HWND _window, UINT _width, UINT _height, BOOL _fullscreen, IDXGISwapChain3** _swap_chain)
{
	DXGI_SAMPLE_DESC sample_desc;
	sample_desc.Count = 1;
	sample_desc.Quality = 0;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreen_desc;
	fullscreen_desc.Windowed = !_fullscreen;

	DXGI_SWAP_CHAIN_DESC1 swap_chain_descriptor = {};
	swap_chain_descriptor.BufferCount = _frame_buffer_count;
	swap_chain_descriptor.Width = _width;
	swap_chain_descriptor.Height = _height;
	swap_chain_descriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_descriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swap_chain_descriptor.SampleDesc = sample_desc;

	IDXGISwapChain1* swap_chain = nullptr;

	TRYFUNC(dxgiFactory->CreateSwapChainForHwnd(_device, _window, &swap_chain_descriptor, &fullscreen_desc, nullptr, &swap_chain));

	*_swap_chain = static_cast<IDXGISwapChain3*>(swap_chain);

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeDescriptorHeap(UINT _frame_buffer_count, IDXGISwapChain3* _swap_chain, ID3D12DescriptorHeap** _rtv_descriptor_heap, UINT* _rtv_descriptor_size, ID3D12Resource** _render_targets)
{
	D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = {};
	rtv_heap_desc.NumDescriptors             = _frame_buffer_count;
	rtv_heap_desc.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtv_heap_desc.Flags                      = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

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

bool Module::Render::DirectX12::Dx12Factory::MakeCommandAllocator(UINT _frame_buffer_count, ID3D12CommandAllocator** _command_allocator)
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

bool Module::Render::DirectX12::Dx12Factory::MakeFence(UINT _frame_buffer_count, ID3D12Fence** _fence, UINT64* _fence_value, HANDLE* fence_event)
{
	for (unsigned int i = 0; i < _frame_buffer_count; i++)
	{
		TRYFUNC(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence[i])));
		_fence_value[i] = 0;
	}

	*fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeRootSignature(ID3DBlob* _signature, ID3D12RootSignature** _root_signature)
{
	TRYFUNC(device->CreateRootSignature(0, _signature->GetBufferPointer(), _signature->GetBufferSize(), IID_PPV_ARGS(_root_signature)));

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeVertexShader(LPCWSTR _path, D3D12_SHADER_BYTECODE* _shader_bytecode)
{
	ID3DBlob* vertex_shader;
	ID3DBlob* error_buff;
	hr = D3DCompileFromFile(_path, nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertex_shader, &error_buff);
	CHECK_BLOB(error_buff);

	_shader_bytecode->BytecodeLength = vertex_shader->GetBufferSize();
	_shader_bytecode->pShaderBytecode = vertex_shader->GetBufferPointer();

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakePixelShader(LPCWSTR _path, D3D12_SHADER_BYTECODE* _shader_bytecode)
{
	ID3DBlob* pixel_shader;
	ID3DBlob* error_buff;
	hr = D3DCompileFromFile(_path, nullptr, nullptr, "main", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixel_shader, &error_buff);
	CHECK_BLOB(error_buff);

	_shader_bytecode->BytecodeLength = pixel_shader->GetBufferSize();
	_shader_bytecode->pShaderBytecode = pixel_shader->GetBufferPointer();

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakeDepthStencilBuffer(ID3D12DescriptorHeap** _descriptor, ID3D12Resource** _buffer, UINT _width, UINT _weight)
{
	D3D12_DESCRIPTOR_HEAP_DESC heap_desc = {};
	heap_desc.NumDescriptors = 1;
	heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	TRYFUNC(device->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(_descriptor)));

	D3D12_DEPTH_STENCIL_VIEW_DESC depth_stencil_desc = {};
	depth_stencil_desc.Format = DXGI_FORMAT_D32_FLOAT;
	depth_stencil_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_desc.Flags = D3D12_DSV_FLAG_NONE;

	D3D12_CLEAR_VALUE depth_optimized_clear_value;
	depth_optimized_clear_value.Format = DXGI_FORMAT_D32_FLOAT;
	depth_optimized_clear_value.DepthStencil.Depth = 1.0f;
	depth_optimized_clear_value.DepthStencil.Stencil = 0;

	CD3DX12_HEAP_PROPERTIES heap_properties(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_RESOURCE_DESC resource_descritor = CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, _width, _weight, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

	device->CreateCommittedResource(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_descritor, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depth_optimized_clear_value, IID_PPV_ARGS(_buffer));
	(*_descriptor)->SetName(L"Depth/Stencil Resource Heap");

	device->CreateDepthStencilView(*_buffer, &depth_stencil_desc, (*_descriptor)->GetCPUDescriptorHandleForHeapStart());

	return true;
}

bool Module::Render::DirectX12::Dx12Factory::MakePipelineStateObject(ID3D12RootSignature* _root_signature, D3D12_SHADER_BYTECODE* _vertex_shader_bytecode, D3D12_SHADER_BYTECODE* _pixel_shader_bytecode, ID3D12PipelineState** _pipeline_state_object)
{
	D3D12_INPUT_ELEMENT_DESC input_layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	D3D12_INPUT_LAYOUT_DESC input_layout_desc;
	input_layout_desc.NumElements = sizeof input_layout / sizeof(D3D12_INPUT_ELEMENT_DESC);
	input_layout_desc.pInputElementDescs = input_layout;

	DXGI_SAMPLE_DESC sample_desc;
	sample_desc.Count = 1;
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
	pso_desc.DSVFormat                          = DXGI_FORMAT_D32_FLOAT;

	TRYFUNC(device->CreateGraphicsPipelineState(&pso_desc, IID_PPV_ARGS(_pipeline_state_object)));

	return true;
}
