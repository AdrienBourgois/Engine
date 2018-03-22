#include "Dx12GraphicObject.h"

namespace Module
{
	namespace Render
	{

		DirectX12::Objects::Dx12GraphicObject::Dx12GraphicObject(unsigned int _id, Core::CoreType::String _name, Core::CoreType::Transform* _transform, ID3D12GraphicsCommandList* _command_list, Core::CoreType::Vertex* _vertices_array, unsigned int _vertices_count, D3D12_VERTEX_BUFFER_VIEW* _vertex_buffer_view, unsigned int* _indexs_array, unsigned int _indexs_count, D3D12_INDEX_BUFFER_VIEW* _index_buffer_view, Dx12ConstantBuffer* _constant_buffer)
			: id(_id), commandList(_command_list), vertexBufferView(_vertex_buffer_view), indexBufferView(_index_buffer_view), constantBuffer(_constant_buffer), name(_name), transform(_transform), vertices(_vertices_array), verticesCount(_vertices_count), indexsArray(_indexs_array), indexsCount(_indexs_count)
		{
			commandList->SetName((_name + S(" Command List")).ToWideString().CStr());
			if (_indexs_array && _indexs_count)
				indexed = true;
		}

		DirectX12::Objects::Dx12GraphicObject::~Dx12GraphicObject()
		{
			SAFE_RELEASE(commandList);

			delete vertexBufferView;
			delete indexBufferView;
		}

		void DirectX12::Objects::Dx12GraphicObject::PrepareCommandList() const
		{
			commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			commandList->IASetVertexBuffers(0, 1, vertexBufferView);

			if (constantBuffer)
				commandList->SetGraphicsRootConstantBufferView(0, constantBuffer->GetResource()->GetGPUVirtualAddress());

			if(IsIndexed())
			{
				commandList->IASetIndexBuffer(indexBufferView);
				commandList->DrawIndexedInstanced(indexsCount, 1, 0, 0, 0);
			}
			else
				commandList->DrawInstanced(verticesCount / 3, 1, 0, 0);
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

		Core::CoreType::Transform* DirectX12::Objects::Dx12GraphicObject::GetTransform() const
		{
			return transform;
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

		DirectX12::Objects::Dx12ConstantBuffer* DirectX12::Objects::Dx12GraphicObject::GetConstantBuffer() const
		{
			return constantBuffer;
		}

		D3D12_INDEX_BUFFER_VIEW* DirectX12::Objects::Dx12GraphicObject::GetIndexBufferView() const
		{
			return indexBufferView;
		}
	}
}