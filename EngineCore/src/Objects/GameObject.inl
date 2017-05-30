#pragma once

template <typename T,  typename... PARAMS>
T* Object::GameObject::CreateComponent(PARAMS... params)
{
	T* component = new T(params...);
	Core::Interface::IComponent* component_cast = static_cast<Core::Interface::IComponent*>(component);

	if (component_cast)
	{
		component_cast->SetAttachedGameObject(this);

		component_cast->SetDefaultComponentName();

		component_cast->SetDefaultComponentType();

		component_cast->Initialize();

		components->push_back(component_cast);
		return component;
	}

	return nullptr;
}

template <typename T>
T* Object::GameObject::GetComponent() const
{
	for (Core::Interface::IComponent* component : *components)
	{
		if (typeid(*component) == typeid(T))
			return static_cast<T*>(component);
	}

	return nullptr;
}

template <typename T>
bool Object::GameObject::HasComponentOfType() const
{
	for (Core::Interface::IComponent* component : *components)
	{
		if (typeid(*component) == typeid(T))
			return true;
	}

	return false;
}
