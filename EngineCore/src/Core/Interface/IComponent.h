#pragma once

#include "Macros.h"

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
		void SetDefaultComponentName() override { componentName = name; }\
		void SetDefaultComponentType() override { id = subtype; }

namespace Core
{
	namespace Interface
	{
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
			void SetComponentName(CoreType::String _new_name = S("")) { componentName = _new_name; };
			/**
			 * \brief Return tha name of component
			 * \return Component name
			 */
			const char* GetComponentName() const { return componentName.CStr(); }

		protected:
			CoreType::String componentName = S("Unamed Component");
			CoreType::Id id = CoreType::Id(CoreType::ObjectComponent);
		};
	}
}