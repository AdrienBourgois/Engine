#include "Dx12RootSignatureDescritor.h"
#include "Modules/Render/DirectX/DX12Helper.h"

ID3DBlob* Module::Render::DirectX12::Objects::Dx12RootSignatureDescritor::GetSignature()
{
	if (needToSerialize)
		SerializeSignature();

	return rootSignature;
}

bool Module::Render::DirectX12::Objects::Dx12RootSignatureDescritor::IsUpdateNeeded() const
{
	return needToSerialize;
}

void Module::Render::DirectX12::Objects::Dx12RootSignatureDescritor::SignatureUpdated()
{
	needToSerialize = false;
}

void Module::Render::DirectX12::Objects::Dx12RootSignatureDescritor::CreateTable()
{
	D3D12_DESCRIPTOR_RANGE* descriptor_table_range = new D3D12_DESCRIPTOR_RANGE();
	descriptor_table_range->RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	descriptor_table_range->NumDescriptors = 1;
	descriptor_table_range->BaseShaderRegister = 0;
	descriptor_table_range->RegisterSpace = 0;
	descriptor_table_range->OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	D3D12_ROOT_DESCRIPTOR_TABLE descriptor_table;
	descriptor_table.NumDescriptorRanges = 1;
	descriptor_table.pDescriptorRanges = descriptor_table_range;

	D3D12_ROOT_PARAMETER  root_parameter;
	root_parameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	root_parameter.DescriptorTable = descriptor_table;
	root_parameter.ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	tables[D3D12_DESCRIPTOR_RANGE_TYPE_CBV] = descriptor_table;
	parameters.push_back(root_parameter);

	needToSerialize = true;
}

void Module::Render::DirectX12::Objects::Dx12RootSignatureDescritor::SerializeSignature()
{
	CD3DX12_ROOT_SIGNATURE_DESC root_signature_desc;
	root_signature_desc.Init(static_cast<UINT>(parameters.size()), parameters.data(), 0, nullptr,
	D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
	D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
	D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
	D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
	D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS);

	D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &rootSignature, nullptr);
}
