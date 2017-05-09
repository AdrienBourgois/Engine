#include "Dx12GraphicObject.h"

namespace Module
{
	namespace Render
	{

		DirectX12::Objects::Dx12GraphicObject::Dx12GraphicObject(unsigned int _id, Core::CoreType::String _name, ID3D12GraphicsCommandList* _command_list, Core::CoreType::Vertex* _vertices_array, unsigned int _vertices_count, D3D12_VERTEX_BUFFER_VIEW* _vertex_buffer_view, unsigned int* _indexs_array, unsigned int _indexs_count, D3D12_INDEX_BUFFER_VIEW* _index_buffer_view)
			: id(_id), commandList(_command_list), vertexBufferView(_vertex_buffer_view), indexBufferView(_index_buffer_view), name(_name), vertices(_vertices_array), verticesCount(_vertices_count), indexsArray(_indexs_array), indexsCount(_indexs_count)
		{
			commandList->SetName((_name + S(" Command List")).ToWideString());
			if (_indexs_array && _indexs_count)
				indexed = true;
		}

		DirectX12::Objects::Dx12GraphicObject::~Dx12GraphicObject()
		{
			SAFE_RELEASE(commandList);

			if (vertexBufferView)
				delete vertexBufferView;
			if (indexBufferView)
				delete indexBufferView;
		}

		void DirectX12::Objects::Dx12GraphicObject::PrepareCommandList() const
		{
			commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			commandList->IASetVertexBuffers(0, 1, vertexBufferView);
			if(IsIndexed())
			{
				commandList->IASetIndexBuffer(indexBufferView);
				commandList->DrawIndexedInstanced(indexsCount, 1, 0, 0, 0);
			}
			else
				commandList->DrawInstanced(3, 1, 0, 0);
		}

		bool DirectX12::Objects::Dx12GraphicObject::IsIndexed() const
		{
			return indexed;
		}

		unsigned DirectX12::Objects::Dx12GraphicObject::GetId() const
		{
			return id;
		}

		ID3D12GraphicsCommandList* DirectX12::Objects::Dx12GraphicObject::GetCommandList() const
		{
			return commandList;
		}

		D3D12_VERTEX_BUFFER_VIEW* DirectX12::Objects::Dx12GraphicObject::GetVertexBufferView() const
		{
			return vertexBufferView;
		}

		unsigned DirectX12::Objects::Dx12GraphicObject::GetVertexCount() const
		{
			return verticesCount;
		}

		unsigned DirectX12::Objects::Dx12GraphicObject::GetIndexCount() const
		{
			return indexsCount;
		}

		D3D12_INDEX_BUFFER_VIEW* DirectX12::Objects::Dx12GraphicObject::GetIndexBufferView() const
		{
			return indexBufferView;
		}
	}
}