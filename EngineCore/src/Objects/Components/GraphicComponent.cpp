#include "GraphicComponent.h"

Object::Component::GraphicComponent::GraphicComponent(Core::CoreType::Vertex _vertexs_array[], unsigned int _vertexs_count, unsigned int _indexs_array[], unsigned int _indexs_count)
{
	vertices.reserve(_vertexs_count);

	for (unsigned int i = 0; i < _vertexs_count; ++i)
		vertices.push_back(_vertexs_array[i]);

	if(_indexs_array && _indexs_count)
	{
		indexs.reserve(_indexs_count);

		for (unsigned int i = 0; i < _indexs_count; ++i)
			indexs.push_back(_indexs_array[i]);
		indexed = true;
	}
}

bool Object::Component::GraphicComponent::Initialize()
{
	return true;
}

bool Object::Component::GraphicComponent::Start()
{
	return true;
}

bool Object::Component::GraphicComponent::Update()
{
	return true;
}

bool Object::Component::GraphicComponent::Destruct()
{
	return true;
}

bool Object::Component::GraphicComponent::IsIndexed() const
{
	return indexed;
}

Core::CoreType::Vertex* Object::Component::GraphicComponent::GetVertices()
{
	return vertices.data();
}

unsigned int* Object::Component::GraphicComponent::GetIndexs()
{
	return indexs.data();
}

int Object::Component::GraphicComponent::GetVertexCount() const
{
	return static_cast<int>(vertices.size());
}

int Object::Component::GraphicComponent::GetIndexCount() const
{
	return static_cast<int>(indexs.size());
}

Core::CoreType::Id Object::Component::GraphicComponent::GetId() const
{
	return id;
}