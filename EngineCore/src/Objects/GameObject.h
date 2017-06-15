#pragma once

#include <vector>

#include "Macros.h"
#include "Core/Interface/IComponent.h"
#include "Core/CoreType/Transform.h"

namespace Object
{
	/**
	 * \brief GameObject with components
	 */
	class ENGINEDLL_API GameObject
	{
	public:
		/**
		 * \brief Default contructor
		 */
		GameObject() = default;
		/**
		 * \brief Constructor
		 * \param _name Name of object
		 */
		explicit GameObject(Core::CoreType::String _name);
		/**
		 * \brief Default destructor
		 */
		~GameObject() = default;

		/**
		 * \brief Return the name of object
		 * \return Object name
		 */
		Core::CoreType::String GetName() const;
		/**
		 * \brief Return the id of object
		 * \return Id of object
		 */
		Core::CoreType::Id GetId() const;

		/**
		 * \brief Return transform of object
		 * \return Transform of object
		 */
		Core::CoreType::Transform GetTransform() const;
		/**
		 * \brief Return a direct pointer to the transform of object
		 * \return Pointer to the object
		 */
		Core::CoreType::Transform* GetTransformReference();
		/**
		 * \brief Set a new transorm to the object
		 * \param _transform New transform
		 * \note This don't invalidate the previous direct pointer
		 */
		void SetTransform(Core::CoreType::Transform _transform);

		/**
		 * \brief Create a component and attched it to this object
		 * \tparam T Type of component
		 * \tparam PARAMS Parameters for component constructor
		 * \return Pointer to the component
		 */
		template <typename T = Core::Interface::IComponent, typename... PARAMS>
		T* CreateComponent(PARAMS...);
		/**
		 * \brief Search the first component of the object by type
		 * \tparam T Type of the component
		 * \return Pointer to th ecomponent
		 */
		template <typename T = Core::Interface::IComponent>
		T* GetComponent() const;
		/**
		 * \brief Search if this object has a component of a type
		 * \tparam T Type of the component
		 * \return Has object a component of this type
		 */
		template <typename T = Core::Interface::IComponent>
		bool HasComponentOfType() const;

	private:
		/**
		 * \brief Store name of object
		 */
		Core::CoreType::String objectName = S("Unnamed GameObject");
		/**
		 * \brief Store id of object
		 */
		Core::CoreType::Id id = Core::CoreType::Id(Core::CoreType::EObjectSubtype::DefaultGameObject);

		/**
		 * \brief Transform of object
		 */
		Core::CoreType::Transform transform;

		/**
		 * \brief Parent of object
		 */
		GameObject* parent = nullptr;
		/**
		 * \brief List of object childs
		 */
		std::vector<GameObject*>* childs = new std::vector<GameObject*>();

		/**
		 * \brief List of components attached to object
		 */
		std::vector<Core::Interface::IComponent*>* components = new std::vector<Core::Interface::IComponent*>();
	};
}

#include "Objects/GameObject.inl"