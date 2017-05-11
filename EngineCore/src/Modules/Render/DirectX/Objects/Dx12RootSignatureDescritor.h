#pragma once

#include "Core/CoreType/String.h"
#include <d3d12.h>
#include <map>
#include <vector>

namespace Module
{
	namespace Render
	{
		namespace DirectX12
		{
			namespace Objects
			{
				/**
				 * \brief Manage Root Signature for Direct X 12
				 * \note This class exist to prevent Root Signature memory overflow and manage slots (see https://msdn.microsoft.com/en-us/library/windows/desktop/dn899209(v=vs.85).aspx#memory_limits_and_costs)
				 */
				class Dx12RootSignatureDescritor
				{
				public:
					Dx12RootSignatureDescritor();
					~Dx12RootSignatureDescritor() = default;

					ID3DBlob* GetSignature();

					bool IsUpdateNeeded() const;
					void SignatureUpdated();

					char GetNewConstantSlot(char _slot_required);

				private:
					ID3DBlob* rootSignature = nullptr;

					bool needToSerialize = false;

					bool slotUsed[64] = { false };
					char currentSlot = 0;

					std::map<D3D12_DESCRIPTOR_RANGE_TYPE, D3D12_ROOT_DESCRIPTOR_TABLE> tables;
					std::vector<D3D12_ROOT_PARAMETER> parameters;

					char CreateTable(unsigned int _size, D3D12_DESCRIPTOR_RANGE_TYPE _type);

					void SerializeSignature();
				};
			}
		}
	}
}

