#pragma once

#include <vector>
#include "Core/CoreType/Vertex.h"
#include "PrimitivesMeshs.h"

namespace Core
{
	namespace CoreType
	{
		/**
		 * \brief Handle vertices and indexs for mesh
		 */
		class Mesh
		{
		public:
			/**
			 * \brief Contructor from vertives (and indexs) array(s)
			 * \param _vertexs_array Array of vertices
			 * \param _vertexs_count Count of vertex in array / Array size
			 * \param _indexs_array Array of indexs (if index buffer needed)
			 * \param _indexs_count Count of indexs in array / Array size (if index buffer needed)
			 */
			explicit Mesh(Vertex _vertexs_array[], unsigned int _vertexs_count, unsigned int _indexs_array[] = {}, unsigned int _indexs_count = 0);
			/**
			 * \brief Contructor from primitive mesh type
			 * \param _mesh_type Type of the primitive mesh
			 */
			explicit Mesh(PrimitiveMesh::PrimitivesMeshType _mesh_type);
			/**
			 * \brief Default destructor
			 */
			~Mesh() = default;

			/**
			 * \brief Specify if vertices are indexed or not
			 * \return Is component indexed
			 */
			bool IsIndexed() const;

			/**
			 * \brief Return an array with vertices
			 * \return Array of vertices
			 */
			Vertex* GetVertices() const;
			/**
			 * \brief Return an array with indexs
			 * \return Array of indexs
			 */
			unsigned int* GetIndexs() const;
			/**
			 * \brief Return the number of vertices
			 * \return Count of vertices
			 */
			int GetVertexCount() const;
			/**
			 * \brief Return the number of indexs
			 * \return Count of indexs
			 */
			int GetIndexCount() const;

		private:
			bool indexed = false;

			void CopyVerticesArray(const Vertex _vertexs_array[], unsigned int _vertexs_count) const;
			void CopyIndexsArray(unsigned int _indexs_array[], unsigned int _indexs_count) const;

			std::vector<Vertex>* vertices = new std::vector<Vertex>();
			std::vector<unsigned int>* indexs = new std::vector<unsigned>();
		};
	}
}

