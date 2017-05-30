#pragma once

#include <vector>

#include "Macros.h"
#include "Core/Interface/IComponent.h"
#include "Core/CoreType/Transform.h"

namespace Object
{
	class ENGINEDLL_API GameObject
	{
	public:
		GameObject() = default;
		explicit GameObject(Core::CoreType::String _name);
		~GameObject() = default;

		Core::CoreType::String GetName() const;
		Core::CoreType::Id GetId() const;

		Core::CoreType::Transform GetTransform() const;
		Core::CoreType::Transform* GetTransformReference();
		void SetTransform(Core::CoreType::Transform _transform);

		template <typename T = Core::Interface::IComponent, typename... PARAMS>
		T* CreateComponent(PARAMS...);
		template <typename T = Core::Interface::IComponent>
		T* GetComponent() const;
		template <typename T = Core::Interface::IComponent>
		bool HasComponentOfType() const;

	private:
		Core::CoreType::String objectName = S("Unnamed GameObject");
		Core::CoreType::Id id = Core::CoreType::Id(Core::CoreType::EObjectSubtype::DefaultGameObject);

		Core::CoreType::Transform transform;

		GameObject* parent = nullptr;
		std::vector<GameObject*>* enfants = new std::vector<GameObject*>();

		std::vector<Core::Interface::IComponent*>* components = new std::vector<Core::Interface::IComponent*>();
	};
}

#include "Objects/GameObject.inl"