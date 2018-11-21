#pragma once

#include <vector>

#include "Core/Interface/IModule.h"
#include "Core/CoreType/String.h"

class Engine;

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
			 * \brief Constructor
			 * \param _engine_reference Reference to engine instance
			 */
			explicit ModuleManager(Engine* _engine_reference);
			/**
			 * \brief Default destructor
			 */
			~ModuleManager() = default;

			/**
			 * \brief Initialize all modules
			 * \return Is all module successfully initialized
			 */
			bool InitializeModules();
			/**
			 * \brief Start all modules
			 * \return Is all modules successfully started
			 */
			bool StartModules();

			/**
			 * \brief Create and add module to Engine
			 * \tparam T Module type (inherit from Core::Interface::IModule class)
			 * \param _name Name of module
			 * \return Is module successfully created
			 */
			template<typename T>
			bool CreateModule(const CoreType::String& _name);

			/**
			 * \brief Return first module found by type
			 * \tparam T Module type (inherit from Core::Interface::IModule class)
			 * \return Module founded (nullptr if any)
			 */
			template<typename T>
			T* GetModule() const;
			/**
			 * \brief Return first module found by type and name
			 * \tparam T Module type (inherit from Core::Interface::IModule class)
			 * \param _name Module name
			 * \return Module founded (nullptr if any)
			 */
			template<typename T>
			T* GetModuleByName(CoreType::String _name) const;

			/**
			 * \brief Update all modules
			 */
			void UpdateModules();

			/**
			 * \brief Stop all modules
			 */
			void Stop();

		private:
			/**
			 * \brief List of modules
			 */
			std::vector<Interface::IModule*> modules;

			/**
			 * \brief Reference to engine instance
			 */
			Engine* engine = nullptr;
		};
	}
}

#include "Core/Manager/ModuleManager.inl"