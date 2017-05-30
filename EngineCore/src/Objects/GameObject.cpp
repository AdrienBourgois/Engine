#include "GameObject.h"

Object::GameObject::GameObject(Core::CoreType::String _name): objectName(_name) {}

Core::CoreType::String Object::GameObject::GetName() const
{
	return objectName;
}

Core::CoreType::Id Object::GameObject::GetId() const
{
	return id;
}

Core::CoreType::Transform Object::GameObject::GetTransform() const
{
	return transform;
}

Core::CoreType::Transform* Object::GameObject::GetTransformReference()
{
	return &transform;
}

void Object::GameObject::SetTransform(Core::CoreType::Transform _transform)
{
	transform = _transform;
}
