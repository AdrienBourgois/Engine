#include "Mesh.h"

Core::CoreType::Mesh::Mesh(Vertex _vertices_array[], const unsigned int _vertices_count, unsigned int _indexes_array[], const unsigned int _indexes_count)
{
	CopyVerticesArray(_vertices_array, _vertices_count);

	if(_indexes_array && _indexes_count)
	{
		CopyIndexesArray(_indexes_array, _indexes_count);
		indexed = true;
	}
}

Core::CoreType::Mesh::Mesh(const PrimitiveMesh::PrimitivesMeshType _mesh_type)
{
	if(_mesh_type == PrimitiveMesh::PrimitivesMeshType::Cube)
	{
		CopyVerticesArray(PrimitiveMesh::CubeVertices, _countof(PrimitiveMesh::CubeVertices));
		CopyIndexesArray(PrimitiveMesh::CubeIndexes, _countof(PrimitiveMesh::CubeIndexes));
		indexed = true;
	}
}

void Core::CoreType::Mesh::SetColor(const Color _color)
{
	for (int i = 0; i < GetVertexCount(); ++i)
	{
		vertices[i].SetColor(_color);
	}
}

bool Core::CoreType::Mesh::IsIndexed() const
{
	return indexed;
}

Core::CoreType::Vertex* Core::CoreType::Mesh::GetVertices() const
{
	return vertices.GetData();
}

unsigned int* Core::CoreType::Mesh::GetIndexes() const
{
	return indexes.GetData();
}

int Core::CoreType::Mesh::GetVertexCount() const
{
	return static_cast<int>(vertices.Size());
}

int Core::CoreType::Mesh::GetIndexCount() const
{
	return static_cast<int>(indexes.Size());
}

void Core::CoreType::Mesh::CopyVerticesArray(const Vertex _vertices_array[], const unsigned int _vertices_count)
{
	vertices.Reserve(_vertices_count);

	for (unsigned int i = 0; i < _vertices_count; ++i)
		vertices.PushBack(_vertices_array[i]);
}

void Core::CoreType::Mesh::CopyIndexesArray(unsigned int _indexes_array[], const unsigned int _indexes_count)
{
	indexes.Reserve(_indexes_count);

	for (unsigned int i = 0; i < _indexes_count; ++i)
		indexes.PushBack(_indexes_array[i]);
}
