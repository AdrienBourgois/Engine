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
				/**
				 * \brief Manage constants buffers, to map and get virtual GPU adresses
				 */
				class Dx12ConstantBuffer
				{
				public:
					/**
					 * \brief Constructor
					 * \param _descriptor_heap Descriptor heap of constant buffer
					 * \param _buffer_upload_heap Upload heap resource of constant buffer
					 */
					explicit Dx12ConstantBuffer(ID3D12DescriptorHeap* _descriptor_heap, ID3D12Resource* _buffer_upload_heap);
					/**
					 * \brief Destructor
					 */
					~Dx12ConstantBuffer();

					/**
					 * \brief Map the buffer to get virtual GPU adress
					 * \return Virtual GPU address mapped
					 */
					UINT8* Map();
					/**
					 * \brief Unmap the buffer
					 */
					void Unmap();

					/**
					 * \brief Return the upload heap resource associated with buffer
					 * \return Upload heap resource
					 */
					ID3D12Resource* GetResource() const;
					/**
					 * \brief Return the descriptor heap of the buffer
					 * \return Descriptor heap of buffer
					 */
					ID3D12DescriptorHeap* GetDescriptorHeap() const;
					/**
					 * \brief Return the virtual GPU adress for this buffer
					 * \return Virtual GPU adress of mapped buffer
					 * \note The buffer must be mapped to get a valid adress, if buffer is unmaped, return nullptr
					 */
					UINT8* GetHeapGpuAdress() const;

				private:
					/**
					 * \brief Is buffer mapped
					 */
					bool isMap = false;

					/**
					 * \brief Buffer upload heap
					 */
					ID3D12Resource* bufferUploadHeap = nullptr;
					/**
					 * \brief Current virtual GPU adress of mapped buffer
					 */
					UINT8* heapGpuAdress = nullptr;
					/**
					 * \brief Descriptor heap of buffer
					 */
					ID3D12DescriptorHeap* descriptorHeap = nullptr;
				};
			}
		}
	}
}

