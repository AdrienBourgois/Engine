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
				/**
				 * \brief Handle datas and buffers from engine Object::Component::GraphicComponent
				 */
				class Dx12GraphicObject
				{
				public:
					/**
					 * \brief Constructor
					 * \param _id Id of object
					 * \param _name Name of object (Mostly used for debug)
					 * \param _command_list Command list to use with this object
					 * \param _vertices_array Array of object vertices
					 * \param _vertices_count Count of vertices in array
					 * \param _vertex_buffer_view Vertex buffer view of object
					 * \param _indexs_array Array of object indexs (if object indexed)
					 * \param _indexs_count Count of indexs in array (if object indexed)
					 * \param _index_buffer_view Index buffer view of object (if object indexed)
					 */
					Dx12GraphicObject(unsigned int _id, Core::CoreType::String _name, ID3D12GraphicsCommandList* _command_list, Core::CoreType::Vertex* _vertices_array, unsigned int _vertices_count, D3D12_VERTEX_BUFFER_VIEW* _vertex_buffer_view, unsigned int* _indexs_array = nullptr, unsigned int _indexs_count = 0, D3D12_INDEX_BUFFER_VIEW* _index_buffer_view = nullptr);
					/**
					 * \brief Destructor
					 */
					~Dx12GraphicObject();

					/**
					 * \brief Prepare commend list of object to render (Called each frame)
					 */
					void PrepareCommandList() const;

					/**
					 * \brief Is vertex buffer indexed
					 * \return Is vertex buffer indexed
					 */
					bool IsIndexed() const;

					/**
					 * \brief Return Id of object
					 * \return Id of object
					 */
					unsigned int GetId() const;
					/**
					 * \brief Return command list of object
					 * \return Command list of object
					 */
					ID3D12GraphicsCommandList* GetCommandList() const;
					/**
					 * \brief Return vertex buffer view of object
					 * \return Vertex buffer view of object
					 */
					D3D12_VERTEX_BUFFER_VIEW* GetVertexBufferView() const;
					/**
					 * \brief Return count of vertices of object
					 * \return Count of vertices of object
					 */
					unsigned int GetVertexCount() const;
					/**
					 * \brief Return index buffer view of object
					 * \return Index buffer view of object
					 */
					D3D12_INDEX_BUFFER_VIEW* GetIndexBufferView() const;
					/**
					 * \brief Return count of indexs of object
					 * \return Count of indexs of object
					 */
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

