#pragma once

template <typename T,  typename... PARAMS>
T* Object::GameObject::CreateComponent(PARAMS... params)
{
	Core::Interface::IComponent* component = static_cast<Core::Interface::IComponent*>(new T(params));

	if (component)
	{
		component->SetDefaultComponentName();

		component->SetDefaultComponentType();

		component->Initialize();

		components.push_back(component);
		return component;
	}

	return nullptr;
}

template <typename T>
T* Object::GameObject::Get() const
{
	for (Core::Interface::IComponent* component : components)
	{
		if (typeid(*component) == typeid(T))
			return static_cast<T*>(component);
	}

	return nullptr;
}

template <typename T>
bool Object::GameObject::Has() const
{
	for (Core::Interface::IComponent* component : components)
	{
		if (typeid(*component) == typeid(T))
			return true;
	}

	return false;
}
