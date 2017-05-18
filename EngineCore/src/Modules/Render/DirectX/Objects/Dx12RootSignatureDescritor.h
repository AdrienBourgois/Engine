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
					Dx12RootSignatureDescritor() = default;
					~Dx12RootSignatureDescritor() = default;

					ID3DBlob* GetSignature();

					bool IsUpdateNeeded() const;
					void SignatureUpdated();

					void CreateTable();

				private:
					ID3DBlob* rootSignature = nullptr;

					bool needToSerialize = true;

					std::map<D3D12_DESCRIPTOR_RANGE_TYPE, D3D12_ROOT_DESCRIPTOR_TABLE> tables;
					std::vector<D3D12_ROOT_PARAMETER> parameters;

					void SerializeSignature();
				};
			}
		}
	}
}

