#pragma once

#include <d3d12.h>

class GraphicCommandList2 : ID3D12GraphicsCommandList
{
public:
	GraphicCommandList2();
	virtual ~GraphicCommandList2();

	HRESULT SetPso(ID3D12PipelineState* _new_pipeline_state);

	HRESULT Reset(ID3D12CommandAllocator* _allocator, ID3D12PipelineState* _pipeline_state);
	HRESULT Reset(ID3D12CommandAllocator* _allocator);
	HRESULT Close();
private:
	bool recordState = true;

	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12PipelineState* pipelineStateObject = nullptr;
};

