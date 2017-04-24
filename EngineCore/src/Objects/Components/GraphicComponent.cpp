#include "GraphicComponent.h"

Object::Component::GraphicComponent::GraphicComponent(Core::CoreType::Vertex _points[], int _size)
{
	for (int i = 0; i < _size; ++i)
	{
		vertexs.push_back(_points[i]);
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

Core::CoreType::Vertex* Object::Component::GraphicComponent::GetPoints()
{
	return vertexs.data();
}

int Object::Component::GraphicComponent::GetSize() const
{
	return static_cast<int>(vertexs.size());
}

Core::CoreType::Id Object::Component::GraphicComponent::GetId() const
{
	return id;
}