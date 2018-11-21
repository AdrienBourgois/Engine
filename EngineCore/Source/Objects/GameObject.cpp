#include "GameObject.h"
#include "Modules/Render/RenderInterface.h"

Object::GameObject::GameObject(const Core::CoreType::String& _name): objectName(_name) {}

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

void Object::GameObject::SetTransform(const Core::CoreType::Transform _transform)
{
	transform = _transform;
}

void Object::GameObject::SetParent(GameObject* _parent)
{
	if (parent)
	{
		parent->RemoveChild(this);
		parent->transform.SetParent(nullptr);
	}

	parent = _parent;
	parent->AddChild(this);
	transform.SetParent(parent->GetTransformReference());
}

void Object::GameObject::MakeMesh(const Core::CoreType::PrimitiveMesh::PrimitivesMeshType _mesh)
{
	Component::GraphicComponent* graphics = CreateComponent<Component::GraphicComponent>(_mesh);
	auto render_interface = Engine::GetInstance()->GetModule<Module::Render::RenderInterface>();
	render_interface->CreateBuffer(graphics);
}

void Object::GameObject::MakeMesh(const Core::CoreType::PrimitiveMesh::PrimitivesMeshType _mesh, const Core::CoreType::Color _color)
{
	Core::CoreType::Mesh mesh = Core::CoreType::Mesh(_mesh);
	mesh.SetColor(_color);
	Component::GraphicComponent* graphics = CreateComponent<Component::GraphicComponent>(mesh);
	auto render_interface = Engine::GetInstance()->GetModule<Module::Render::RenderInterface>();
	render_interface->CreateBuffer(graphics);
}


void Object::GameObject::AddChild(GameObject* _child) const
{
	childs->push_back(_child);
}

void Object::GameObject::RemoveChild(GameObject* _child) const
{
	const std::_Vector_iterator<std::_Vector_val<std::_Simple_types<GameObject*>>> element = find(childs->begin(), childs->end(), _child);
	if (element != childs->end())
		childs->erase(element);
}
