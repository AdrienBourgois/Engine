#pragma once

#include <vector>

#include "Macros.h"
#include "Core/Interface/IComponent.h"

namespace Object
{
	class GameObject
	{
	public:
		ENGINEDLL_API GameObject() = default;
		ENGINEDLL_API ~GameObject() = default;

		template <typename T = Core::Interface::IComponent>
		ENGINEDLL_API T* CreateComponent(Core::CoreType::String _nameComponent = S(""));
		template <typename T = Core::Interface::IComponent>
		ENGINEDLL_API T* Get() const;

	private:
		Core::CoreType::String ObjectName = S("");
		std::vector<Core::Interface::IComponent*> components;
		Core::CoreType::Id id = Core::CoreType::Id(Core::CoreType::EObjectSubtype::DefaultGameObject);
	};
}

template <typename T>
T* Object::GameObject::CreateComponent(Core::CoreType::String _nameComponent)
{
	Core::Interface::IComponent* component = static_cast<Core::Interface::IComponent*>(new T);

	if (component)
	{
		if (!_nameComponent)
			component->SetDefaultComponentName();
		else
			component->SetComponentName(_nameComponent);

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

