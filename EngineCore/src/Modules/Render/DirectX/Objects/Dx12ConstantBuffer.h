#pragma once

#include <d3d12.h>

namespace Module
{
	namespace Render
	{
		namespace DirectX12
		{
			namespace Objects
			{
				class Dx12ConstantBuffer
				{
				public:
					explicit Dx12ConstantBuffer(ID3D12DescriptorHeap* _descriptor_heap, ID3D12Resource* _buffer_upload_heap);
					~Dx12ConstantBuffer();

					UINT8* Map();
					void Unmap();

					ID3D12DescriptorHeap* GetDescriptorHeap() const;
					UINT8* GetHeapGpuAdress() const;

				private:
					bool isMap = false;

					ID3D12Resource* bufferUploadHeap = nullptr;
					UINT8* heapGpuAdress = nullptr;
					ID3D12DescriptorHeap* descriptorHeap = nullptr;
				};
			}
		}
	}
}

