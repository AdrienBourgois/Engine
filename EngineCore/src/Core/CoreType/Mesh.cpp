#include "Mesh.h"

Core::CoreType::Mesh::Mesh(Vertex _vertexs_array[], unsigned int _vertexs_count, unsigned int _indexs_array[], unsigned int _indexs_count)
{
	CopyVerticesArray(_vertexs_array, _vertexs_count);

	if(_indexs_array && _indexs_count)
	{
		CopyIndexsArray(_indexs_array, _indexs_count);
		indexed = true;
	}
}

Core::CoreType::Mesh::Mesh(PrimitiveMesh::PrimitivesMeshType _mesh_type)
{
	if(_mesh_type == PrimitiveMesh::PrimitivesMeshType::Cube)
	{
		CopyVerticesArray(PrimitiveMesh::CubeVertices, _countof(PrimitiveMesh::CubeVertices));
		CopyIndexsArray(PrimitiveMesh::CubeIndexs, _countof(PrimitiveMesh::CubeIndexs));
		indexed = true;
	}
}

bool Core::CoreType::Mesh::IsIndexed() const
{
	return indexed;
}

Core::CoreType::Vertex* Core::CoreType::Mesh::GetVertices() const
{
	return vertices->data();
}

unsigned int* Core::CoreType::Mesh::GetIndexs() const
{
	return indexs->data();
}

int Core::CoreType::Mesh::GetVertexCount() const
{
	return static_cast<int>(vertices->size());
}

int Core::CoreType::Mesh::GetIndexCount() const
{
	return static_cast<int>(indexs->size());
}

void Core::CoreType::Mesh::CopyVerticesArray(const Vertex _vertexs_array[], unsigned int _vertexs_count) const
{
	vertices->reserve(_vertexs_count);

	for (unsigned int i = 0; i < _vertexs_count; ++i)
		vertices->push_back(_vertexs_array[i]);
}

void Core::CoreType::Mesh::CopyIndexsArray(unsigned int _indexs_array[], unsigned int _indexs_count) const
{
	indexs->reserve(_indexs_count);

	for (unsigned int i = 0; i < _indexs_count; ++i)
		indexs->push_back(_indexs_array[i]);
}
