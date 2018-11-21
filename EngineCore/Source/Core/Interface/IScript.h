#pragma once

#include "Core/CoreType/String.h"
#include "Core/CoreType/Id.h"

/**
 * \brief Used to declare IScript functions and set default script name
 * \param name Default name for script
 * \param subtype Indicate the subtype of script (see Core::CoreType::EObjectSubtype)
 */
#define DECLARE_SCRIPT(name, subtype) \
		void SetDefaultScriptName() override { scriptName = name; } \
		void SetDefaultScriptType() override { id = subtype; }

namespace Core
{
	namespace Interface
	{
		/**
		 * \brief Interface to create scripts
		 */
		class ENGINEDLL_API IScript
		{
			public:
			/**
			 * \brief Default virtual destructor
			 */
			virtual ~IScript() = default;

			/**
			 * \brief Initialize script
			 * \return Is initialization successful
			 */
			virtual void Initialize() {}
			/**
			 * \brief Start script
			 * \return Is start successful
			 */
			virtual void Start() {}
			/**
			 * \brief Update script
			 * \return Is update successful
			 */
			virtual void Update() {}
			/**
			 * \brief Update script with delta time
			 * \param _delta Delta time
			 * \return Is update successful
			 */
			virtual void Update(const float _delta) {}
			/**
			 * \brief Stop and destruct script
			 * \return Is destruction successful
			 */
			virtual void Destruct() {}
			/**
			 * \brief Set a default name for script
			 */
			virtual void SetDefaultScriptName() = 0;
			/**
			 * \brief Set a default type for script id
			 */
			virtual void SetDefaultScriptType() = 0;

			/**
			 * \brief Set a new name for script
			 * \param _newName New name
			 */
			void SetScriptName(const CoreType::String& _newName = S("Unnamed script")) { scriptName = _newName; }
			/**
			 * \brief Return tha name of script
			 * \return Script name
			 */
			CoreType::String GetScriptName() const { return scriptName; }

		protected:
			/**
			 * \brief Store script name
			 */
			CoreType::String scriptName = S("Unnamed Script");
			/**
			 * \brief Store script id
			 */
			CoreType::Id id = CoreType::Id(CoreType::EObjectType::Script);
		};
	}
}
