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
			 * \brief Set a new name for module
			 * \param _new_name New name
			 */
			void SetModuleName(CoreType::String _new_name = S("Unnamed Module")) { moduleName = _new_name; }
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
		};
	}
}