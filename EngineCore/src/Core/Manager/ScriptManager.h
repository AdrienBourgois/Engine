#pragma once

#include <vector>

#include "Core/Interface/IScript.h"
#include "Core/CoreType/String.h"
#include <queue>

namespace Core
{
	namespace Manager
	{
		/**
		 * \brief Handle scripts for Engine
		 */
		class ScriptManager
		{
		public:
			/**
			 * \brief Default constructor
			 */
			ScriptManager() = default;
			/**
			 * \brief Default destructor
			 */
			~ScriptManager() = default;

			/**
			 * \brief Add script class to Engine
			 * \tparam T Script class
			 * \return Is script sucessfully created
			 */
			template <typename T, class U = typename std::enable_if<std::is_base_of<Interface::IScript, T>::value, T>::type>
			bool AddScript();
			/**
			 * \brief Start all scripts
			 * \return Is all scripts sucessfully started
			 */
			bool StartScripts();

			/**
			 * \brief Return first script found by type and name
			 * \tparam T Script type (inherit from Core::Interface::IScript class)
			 * \param _name Script name
			 * \return Script founded (nullptr if any)
			 */
			template<typename T = Interface::IScript>
			T* GetScriptByName(CoreType::String _name) const;

			/**
			 * \brief Return first script found by name as Core::Interface::IScript
			 * \param _name Script name
			 * \return Script founded (nullptr if any)
			 */
			Interface::IScript* GetIScriptByName(CoreType::String _name) const;

			/**
			 * \brief Update all scripts
			 */
			void UpdateScripts();
			/**
			 * \brief Stop all scripts
			 */
			void Stop();

		private:
			/**
			 * \brief List of scripts
			 */
			std::vector<Interface::IScript*> scripts;
			/**
			 * \brief List fo script to start at the next frame
			 */
			std::queue<Interface::IScript*> scriptsToStart;
		};
	}
}

#include "Core/Manager/ScriptManager.inl"