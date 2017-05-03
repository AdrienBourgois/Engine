#include "Dx12GraphicObject.h"

namespace Module
{
	namespace Render
	{

		DirectX12::Objects::Dx12GraphicObject::Dx12GraphicObject(unsigned _id, const Core::CoreType::Vertex* _vertex, Core::CoreType::String _name, ID3D12GraphicsCommandList* _command_list, D3D12_VERTEX_BUFFER_VIEW* _buffer_view)
			: id(_id), commandList(_command_list), bufferView(_buffer_view), name(_name), vertex(_vertex)
		{
			commandList->SetName((_name + S(" Command List")).ToWideString());
		}

		DirectX12::Objects::Dx12GraphicObject::~Dx12GraphicObject()
		{
			SAFE_RELEASE(commandList);

			if (bufferView)
				delete bufferView;
		}

		void DirectX12::Objects::Dx12GraphicObject::PrepareCommandList() const
		{
			commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			commandList->IASetVertexBuffers(0, 1, bufferView);
			commandList->DrawInstanced(3, 1, 0, 0);
		}

		unsigned DirectX12::Objects::Dx12GraphicObject::GetId() const
		{
			return id;
		}

		ID3D12GraphicsCommandList* DirectX12::Objects::Dx12GraphicObject::GetCommandList() const
		{
			return commandList;
		}

		D3D12_VERTEX_BUFFER_VIEW* DirectX12::Objects::Dx12GraphicObject::GetBufferView() const
		{
			return bufferView;
		}
	}
}