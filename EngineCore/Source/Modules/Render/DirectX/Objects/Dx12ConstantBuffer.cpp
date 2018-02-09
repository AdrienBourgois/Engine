#include "Dx12ConstantBuffer.h"
#include "Modules/Render/DirectX/DX12Helper.h"

Module::Render::DirectX12::Objects::Dx12ConstantBuffer::Dx12ConstantBuffer(ID3D12DescriptorHeap* _descriptor_heap, ID3D12Resource* _buffer_upload_heap)
: bufferUploadHeap(_buffer_upload_heap), descriptorHeap(_descriptor_heap)
{}

Module::Render::DirectX12::Objects::Dx12ConstantBuffer::~Dx12ConstantBuffer()
{
	bufferUploadHeap->Release();
	descriptorHeap->Release();
}

UINT8* Module::Render::DirectX12::Objects::Dx12ConstantBuffer::Map()
{
	if(isMap)
		return this->heapGpuAdress;

	CD3DX12_RANGE readRange(0, 0);
	bufferUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&heapGpuAdress));

	isMap = true;

	return heapGpuAdress;
}

void Module::Render::DirectX12::Objects::Dx12ConstantBuffer::Unmap()
{
	if(!isMap)
		return;

	CD3DX12_RANGE readRange(0, 0);
	bufferUploadHeap->Unmap(0, &readRange);

	heapGpuAdress = nullptr;

	isMap = false;
}

ID3D12Resource * Module::Render::DirectX12::Objects::Dx12ConstantBuffer::GetResource() const
{
	return bufferUploadHeap;
}

ID3D12DescriptorHeap* Module::Render::DirectX12::Objects::Dx12ConstantBuffer::GetDescriptorHeap() const
{
	return descriptorHeap;
}

UINT8* Module::Render::DirectX12::Objects::Dx12ConstantBuffer::GetHeapGpuAdress() const
{
	return heapGpuAdress;
}
