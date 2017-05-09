#pragma once

#include <d3d12.h>
#include "Core/CoreType/String.h"
#include "Core/CoreType/Vertex.h"

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) \
   if(x != NULL)        \
   {                    \
	  x->Release();     \
	  x = NULL;         \
   }
#endif

namespace Core {
	namespace CoreType {
		class Vertex;
	}
}

namespace Module
{
	namespace Render
	{
		namespace DirectX12
		{
			namespace Objects
			{
				class Dx12GraphicObject
				{
				public:
					Dx12GraphicObject(unsigned int _id, Core::CoreType::String _name, ID3D12GraphicsCommandList* _command_list, Core::CoreType::Vertex* _vertices_array, unsigned int _vertices_count, D3D12_VERTEX_BUFFER_VIEW* _vertex_buffer_view, unsigned int* _indexs_array = nullptr, unsigned int _indexs_count = 0, D3D12_INDEX_BUFFER_VIEW* _index_buffer_view = nullptr);
					~Dx12GraphicObject();

					void PrepareCommandList() const;

					bool IsIndexed() const;

					unsigned int GetId() const;
					ID3D12GraphicsCommandList* GetCommandList() const;
					D3D12_VERTEX_BUFFER_VIEW* GetVertexBufferView() const;
					unsigned int GetVertexCount() const;
					D3D12_INDEX_BUFFER_VIEW* GetIndexBufferView() const;
					unsigned int GetIndexCount() const;

				private:
					bool indexed = false;

					unsigned int id = 0;
					ID3D12GraphicsCommandList* commandList = nullptr;
					D3D12_VERTEX_BUFFER_VIEW* vertexBufferView = nullptr;
					D3D12_INDEX_BUFFER_VIEW* indexBufferView = nullptr;
					Core::CoreType::String name = S("Unnamed DX12 Graphic Object");

					Core::CoreType::Vertex* vertices = nullptr;
					unsigned int verticesCount = 0;
					unsigned int* indexsArray = nullptr;
					unsigned int indexsCount = 0;
				};
			}
		}
	}
}

