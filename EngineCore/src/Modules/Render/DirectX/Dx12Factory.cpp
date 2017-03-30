#include "Modules/Render/DirectX/Dx12Factory.h"

#include <D3Dcompiler.h>
#include "Modules/Render/DirectX/DX12Helper.h"
#include "Core/CoreType/Vertex.h"
#include "Macros.h"

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

		TRYFUNC(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr));
		if (SUCCEEDED(hr))
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

bool Module::Render::DirectX12::Dx12Factory::MakeSwapChain(IUnknown* _device ,UINT _frame_buffer_count, HWND _window, UINT _width, UINT _height, BOOL _fullscreen, ID3D12CommandQueue* _commandQueue, IDXGISwapChain3** _swap_chain)
{
	DXGI_SAMPLE_DESC sample_desc;
	sample_desc.Count = 1;
	sample_desc.Quality = 0;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreen_desc;
	fullscreen_desc.Windowed = !_fullscreen;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = _frame_buffer_count;
	swapChainDesc.Width = _width;
	swapChainDesc.Height = _height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc = sample_desc;

	IDXGISwapChain1* swapChain = nullptr;

	TRYFUNC(dxgiFactory->CreateSwapChainForHwnd(_device, _window, &swapChainDesc, &fullscreen_desc, nullptr, &swapChain));

	*_swap_chain = static_cast<IDXGISwapChain3*>(swapChain);

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

bool Module::Render::DirectX12::Dx12Factory::MakeCommandList(UINT _frame_buffer_count, ID3D12CommandAllocator** _command_allocator, ID3D12GraphicsCommandList** _command_list)
{
	for (unsigned int i = 0; i < _frame_buffer_count; i++)
	{
		TRYFUNC(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_command_allocator[i])));
	}

	TRYFUNC(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _command_allocator[0], nullptr, IID_PPV_ARGS(_command_list)));

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

bool Module::Render::DirectX12::Dx12Factory::MakeRootSignature(ID3D12RootSignature** _root_signature)
{
	CD3DX12_ROOT_SIGNATURE_DESC root_signature_desc;
	root_signature_desc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ID3DBlob* signature;
	TRYFUNC(D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, nullptr));

	TRYFUNC(device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(_root_signature)));

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

bool Module::Render::DirectX12::Dx12Factory::MakePipelineStateObject(ID3D12RootSignature* _root_signature, D3D12_SHADER_BYTECODE* _vertex_shader_bytecode, D3D12_SHADER_BYTECODE* _pixel_shader_bytecode, ID3D12PipelineState** _pipeline_state_object)
{
	D3D12_INPUT_ELEMENT_DESC input_layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	D3D12_INPUT_LAYOUT_DESC input_layout_desc = {};
	input_layout_desc.NumElements = sizeof(input_layout) / sizeof(D3D12_INPUT_ELEMENT_DESC);
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

	TRYFUNC(device->CreateGraphicsPipelineState(&pso_desc, IID_PPV_ARGS(_pipeline_state_object)));

	return true;
}
