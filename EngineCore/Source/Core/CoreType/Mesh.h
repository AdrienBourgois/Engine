#pragma once

#include "Core/CoreType/Vertex.h"
#include "PrimitivesMeshs.h"
#include "Container/Vector.h"

namespace Core
{
	namespace CoreType
	{
		/**
		 * \brief Handle vertices and indexes for mesh
		 */
		class Mesh
		{
		public:
			/**
			 * \brief Constructor from vertices (and indexes) array(s)
			 * \param _vertices_array Array of vertices
			 * \param _vertices_count Count of vertex in array / Array size
			 * \param _indexes_array Array of indexes (if index buffer needed)
			 * \param _indexes_count Count of indexes in array / Array size (if index buffer needed)
			 */
			explicit Mesh(Vertex _vertices_array[], unsigned int _vertices_count, unsigned int _indexes_array[] = {}, unsigned int _indexes_count = 0);
			/**
			 * \brief Constructor from primitive mesh type
			 * \param _mesh_type Type of the primitive mesh
			 */
			explicit Mesh(PrimitiveMesh::PrimitivesMeshType _mesh_type);
			/**
			 * \brief Default destructor
			 */
			~Mesh() = default;

			/**
			 * \brief Change color of mesh
			 * \param _color Mew color
			 */
			void SetColor(Color _color);

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
			 * \brief Return an array with indexes
			 * \return Array of indexes
			 */
			unsigned int* GetIndexes() const;
			/**
			 * \brief Return the number of vertices
			 * \return Count of vertices
			 */
			int GetVertexCount() const;
			/**
			 * \brief Return the number of indexes
			 * \return Count of indexes
			 */
			int GetIndexCount() const;

		private:
			/**
			 * \brief Is mesh indexed
			 */
			bool indexed = false;

			/**
			 * \brief Copy list of vertices in this mesh
			 * \param _vertices_array List of vertices
			 * \param _vertices_count Count of vertices
			 */
			void CopyVerticesArray(const Vertex _vertices_array[], unsigned int _vertices_count);
			/**
			 * \brief Copy list of indexes in this mesh
			 * \param _indexes_array List of indexes
			 * \param _indexes_count Count of indexes
			 */
			void CopyIndexesArray(unsigned int _indexes_array[], unsigned int _indexes_count);

			/**
			 * \brief Store vertices
			 */
			Container::Vector<Vertex> vertices;
			/**
			 * \brief Store indexes
			 */
			Container::Vector<unsigned int> indexes;
		};
	}
}

