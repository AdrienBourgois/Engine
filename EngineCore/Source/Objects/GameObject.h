#pragma once

#include <vector>

#include "Macros.h"
#include "Core/Interface/IComponent.h"
#include "Core/CoreType/Transform.h"

namespace Core {
	namespace CoreType {
		namespace PrimitiveMesh {
			enum class PrimitivesMeshType;
		}
		class Color;
	}
}

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
		explicit GameObject(const Core::CoreType::String& _name);
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
		template <typename T,  typename... PARAMS, class U = typename std::enable_if<std::is_base_of<Core::Interface::IComponent, T>::value, T>::type>
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

		/**
		 * \brief Set a new parent to this object
		 * \param _parent New parent for object
		 */
		void SetParent(GameObject* _parent);

		/**
		 * \brief Create a mesh for attached game object
		 * \param _mesh Mesh type
		 */
		void MakeMesh(Core::CoreType::PrimitiveMesh::PrimitivesMeshType _mesh);

		/**
		 * \brief Create a mesh for attached game object
		 * \param _mesh Mesh type
		 * \param _color Color of mesh
		 */
		void MakeMesh(Core::CoreType::PrimitiveMesh::PrimitivesMeshType _mesh, Core::CoreType::Color _color);

	private:
		/**
		 * \brief Add a new child to this object
		 * \param _child New child
		 */
		void AddChild(GameObject* _child) const;
		/**
		 * \brief Remove a child to this object
		 * \param _child Child to remove
		 */
		void RemoveChild(GameObject* _child) const;

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