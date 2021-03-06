#pragma once

#include "Engine.h"

namespace Object
{
	class GameObject;
}

/**
 * \brief Used to declare IComponent functions and set default component name
 * \param name Default name for component
 * \param subtype Indicate the subtype of component (see Core::CoreType::EObjectSubtype)
 */
#define DECLARE_COMPONENT(name, subtype) \
		bool Initialize() override;\
		bool Start() override;\
		bool Update() override;\
		bool Destruct() override;\
		void SetAttachedGameObject(Object::GameObject* _game_object) override { gameObjectReference = _game_object; }\
		void SetDefaultComponentName() override { componentName = name; }\
		void SetDefaultComponentType() override { id = subtype; }

namespace Core
{
	namespace Interface
	{
		/**
		 * \brief Interface for GameObject components
		 */
		class ENGINEDLL_API IComponent
		{
		public:
			/**
			 * \brief Default virtual destructor
			 */
			virtual ~IComponent() = default;

			/**
			 * \brief Initialize component
			 * \return Is initialization sucessfull
			 */
			virtual bool Initialize() = 0;
			/**
			 * \brief Start component
			 * \return Is start sucessfull
			 */
			virtual bool Start() = 0;
			/**
			 * \brief Update component
			 * \return Is update sucessfull
			 */
			virtual bool Update() = 0;
			/**
			 * \brief Stop and destruct component
			 * \return Is desctruction sucessfull
			 */
			virtual bool Destruct() = 0;
			/**
			 * \brief Set the owner GameObject
			 * \param _game_object GameObject that own this component
			 */
			virtual void SetAttachedGameObject(Object::GameObject* _game_object) = 0;
			/**
			 * \brief Set a default name for component
			 */
			virtual void SetDefaultComponentName() = 0;
			/**
			 * \brief Set a default type for component id
			 */
			virtual void SetDefaultComponentType() = 0;

			/**
			 * \brief Set a new name for component
			 * \param _new_name New name
			 */
			void SetComponentName(CoreType::String _new_name = S("Unnamed Component")) { componentName = _new_name; }
			/**
			 * \brief Return tha name of component
			 * \return Component name
			 */
			CoreType::String GetComponentName() const { return componentName; }
			/**
			 * \brief Return a reference to GameObject
			 * \return Pointer to Object::GameObject
			 */
			Object::GameObject* GameObject() const { return gameObjectReference; }

		protected:
			/**
			 * \brief Store reference to the GameObject that this component is attached
			 */
			Object::GameObject* gameObjectReference = nullptr;
			/**
			 * \brief Store component name
			 */
			CoreType::String componentName = S("Unnamed Component");
			/**
			 * \brief Store component id
			 */
			CoreType::Id id = CoreType::Id(CoreType::EObjectType::ObjectComponent);
		};
	}
}