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

		template <typename T = Core::Interface::IComponent, typename... PARAMS>
		ENGINEDLL_API T* CreateComponent(PARAMS...);
		template <typename T = Core::Interface::IComponent>
		ENGINEDLL_API T* Get() const;
		template <typename T = Core::Interface::IComponent>
		ENGINEDLL_API bool Has() const;

	private:
		Core::CoreType::String ObjectName = S("Unnamed GameObject");
		std::vector<Core::Interface::IComponent*> components;
		Core::CoreType::Id id = Core::CoreType::Id(Core::CoreType::EObjectSubtype::DefaultGameObject);
	};
}

#include "Objects/GameObject.inl"