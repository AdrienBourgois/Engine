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
			 * \return Is all modules sucessfully stared
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
			T* GetModuleByName(char* _name) const;

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
			Interface::IModule* GetIModuleByName(char* _name) const;

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

template <typename T>
bool Core::Manager::ModuleManager::CreateModule(CoreType::String _name)
{
	Interface::IModule * module = static_cast<Interface::IModule*>(new T);

	if (module)
	{
		if (!_name)
			module->SetDefaultModuleName();
		else
			module->SetModuleName(_name);

		module->Initialize();

		modules.push_back(module);
		return true;
	}

	return false;
}

template<typename T>
T* Core::Manager::ModuleManager::GetModule() const
{
	for (Interface::IModule* module : modules)
	{
		if (typeid(*module) == typeid(T))
			return static_cast<T*>(module);
	}

	return nullptr;
}

template<typename T>
T* Core::Manager::ModuleManager::GetModuleByName(char* _name) const
{
	for (Interface::IModule* module : modules)
	{
		if (module->GetModuleName() == _name)
			return static_cast<T*>(module);
	}

	return nullptr;
}

template<typename T>
Core::Interface::IModule* Core::Manager::ModuleManager::GetIModule() const
{
	for (Interface::IModule* module : modules)
	{
		if (typeid(*module) == typeid(T))
			return module;
	}

	return nullptr;
}