#pragma once

#include <vector>

#include "Core/Interface/IModule.h"
#include "Core/CoreType/String.h"

namespace Core
{
	namespace Manager
	{
		/**
		 * \brief Handle modules for Engine
		 */
		class ModuleManager
		{
		public:
			/**
			 * \brief Default constructor
			 */
			ModuleManager() = default;
			/**
			 * \brief Default destructor
			 */
			~ModuleManager() = default;

			/**
			 * \brief Initialize all modules
			 * \return Is all module sucessfully initialized
			 */
			bool InitializeModules();
			/**
			 * \brief Start all modules
			 * \return Is all modules sucessfully started
			 */
			bool StartModules();

			/**
			 * \brief Create and add module to Engine
			 * \tparam T Module type (inherit from Core::Interface::IModule class)
			 * \param _name Name of module
			 * \return Is module sucessfully created
			 */
			template<typename T = Interface::IModule>
			bool CreateModule(CoreType::String _name);

			/**
			 * \brief Return first module found by type
			 * \tparam T Module type (inherit from Core::Interface::IModule class)
			 * \return Module founded (nullptr if any)
			 */
			template<typename T = Interface::IModule>
			T* GetModule() const;
			/**
			 * \brief Return first module found by type and name
			 * \tparam T Module type (inherit from Core::Interface::IModule class)
			 * \param _name Module name
			 * \return Module founded (nullptr if any)
			 */
			template<typename T = Interface::IModule>
			T* GetModuleByName(CoreType::String _name) const;

			/**
			 * \brief Return first module found by type as Core::Interface::IModule
			 * \tparam T Module type (inherit from Core::Interface::IModule class)
			 * \return Module founded (nullptr if any)
			 */
			template<typename T = Interface::IModule>
			Interface::IModule* GetIModule() const;
			/**
			 * \brief Return first module found by name as Core::Interface::IModule
			 * \param _name Module name
			 * \return Module founded (nullptr if any)
			 */
			Interface::IModule* GetIModuleByName(CoreType::String _name) const;

			/**
			 * \brief Update all modules
			 */
			void UpdateModules();
			//void StopModule(char _module_type);
			/**
			 * \brief Stop all modules
			 */
			void Stop();

		private:
			/**
			 * \brief List of modules
			 */
			std::vector<Interface::IModule*> modules;
		};
	}
}

#include "Core/Manager/ModuleManager.inl"