#include "GraphicComponent.h"
#include "Objects/GameObject.h"

Object::Component::GraphicComponent::GraphicComponent(Core::CoreType::Vertex _vertexs_array[], unsigned int _vertexs_count, unsigned int _indexs_array[], unsigned int _indexs_count)
{
	mesh = new Core::CoreType::Mesh(_vertexs_array, _vertexs_count, _indexs_array, _indexs_count);
}

Object::Component::GraphicComponent::GraphicComponent(Core::CoreType::PrimitiveMesh::PrimitivesMeshType _mesh_type)
{
	mesh = new Core::CoreType::Mesh(_mesh_type);
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

Core::CoreType::Transform Object::Component::GraphicComponent::GetTransform() const
{
	return gameObjectReference->GetTransform();
}

Core::CoreType::Transform* Object::Component::GraphicComponent::GetTransformReference() const
{
	return gameObjectReference->GetTransformReference();
}

Core::CoreType::Mesh* Object::Component::GraphicComponent::GetMesh() const
{
	return mesh;
}

Core::CoreType::Id Object::Component::GraphicComponent::GetId() const
{
	return id;
}
