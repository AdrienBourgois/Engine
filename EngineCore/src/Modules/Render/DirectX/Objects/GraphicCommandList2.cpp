#include "GraphicCommandList2.h"

GraphicCommandList2::GraphicCommandList2() : ID3D12GraphicsCommandList()
{}


GraphicCommandList2::~GraphicCommandList2()
{}

HRESULT GraphicCommandList2::SetPso(ID3D12PipelineState* _new_pipeline_state)
{
	pipelineStateObject = _new_pipeline_state;

	return TRUE;
}

HRESULT GraphicCommandList2::Reset(ID3D12CommandAllocator* _allocator, ID3D12PipelineState* _pipeline_state)
{
	pipelineStateObject = _pipeline_state;
	return ID3D12GraphicsCommandList::Reset(_allocator, _pipeline_state);
}

HRESULT GraphicCommandList2::Reset(ID3D12CommandAllocator* _allocator)
{
	if (recordState)
		return TRUE;

	recordState = true;
	return Reset(_allocator, pipelineStateObject);
}

HRESULT GraphicCommandList2::Close()
{
	if (!recordState)
		return TRUE;

	recordState = false;
	return ID3D12GraphicsCommandList::Close();
}
