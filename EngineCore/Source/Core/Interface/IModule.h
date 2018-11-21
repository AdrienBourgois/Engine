#pragma once

#include "Core/CoreType/String.h"

/**
 * \brief Used to declare IModule functions and set default module name
 * \param name Default name for module
 */
#define DECLARE_MODULE(name)\
		bool Initialize() override;\
		bool Start() override;\
		bool Update() override;\
		bool Destruct() override;\
		void SetDefaultModuleName() override { moduleName = name; }

class Engine;

namespace Core
{
	namespace Interface
	{
		/**
		 * \brief Interface to create engine module
		 */
		class ENGINEDLL_API IModule
		{
		public:
			/**
			 * \brief Default virtual destructor
			 */
			virtual ~IModule() = default;

			/**
			 * \brief Initialize module
			 * \return Is initialization successful
			 * \note First safe place to call engine and modules elements
			 */
			virtual bool Initialize() = 0;
			/**
			 * \brief Start module
			 * \return Is start successful
			 */
			virtual bool Start() = 0;
			/**
			 * \brief Update module
			 * \return Is update successful
			 */
			virtual bool Update() = 0;
			/**
			 * \brief Stop and destruct module
			 * \return Is destruction successful
			 */
			virtual bool Destruct() = 0;
			/**
			 * \brief Set a default name for module
			 */
			virtual void SetDefaultModuleName() = 0;

			/**
			 * \brief Set reference to engine instance
			 * \param _engine_reference Reference to engine instance
			 */
			void SetEngineInstance(Engine* _engine_reference) { engine = _engine_reference; }

			/**
			 * \brief Return first module found by type
			 * \tparam T Module type (inherit from Core::Interface::IModule class)
			 * \return Module founded (nullptr if any)
			 */
			template<typename T>
			T* Module() const { return engine->GetModule<T>(); }

			/**
			 * \brief Set a new name for module
			 * \param _new_name New name
			 */
			void SetModuleName(const CoreType::String& _new_name = S("Unnamed Module")) { moduleName = _new_name; }
			/**
			 * \brief Return name of module
			 * \return Module name
			 */
			CoreType::String GetModuleName() const { return moduleName; }

		protected:
			/**
			 * \brief Module name
			 */
			CoreType::String moduleName = S("Unnamed Module");

			/**
			 * \brief Engine reference
			 * \note Set after constructor, don't use it before Initialize()
			 */
			Engine* engine = nullptr;
		};
	}
}