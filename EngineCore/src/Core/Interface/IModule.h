#pragma once

#include "Macros.h"
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
			 * \return Is initialization sucessfull
			 */
			virtual bool Initialize() = 0;
			/**
			 * \brief Start module
			 * \return Is start sucessfull
			 */
			virtual bool Start() = 0;
			/**
			 * \brief Update module
			 * \return Is update sucessfull
			 */
			virtual bool Update() = 0;
			/**
			 * \brief Stop and destruct module
			 * \return Is desctruction sucessfull
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
			void SetModuleName(CoreType::String _new_name = S("")) { moduleName = _new_name; };
			/**
			 * \brief Return tha name of module
			 * \return Module name
			 */
			const char* GetModuleName() const { return moduleName.CStr(); }

		protected:
			/**
			 * \brief Module name
			 */
			CoreType::String moduleName = S("Unamed Module");
		};
	}
}