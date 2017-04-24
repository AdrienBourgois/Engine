#pragma once

#include <vector>
#include <fstream>

#include "Modules/Tools/Logger/Log.h"
#include "Core/Interface/IModule.h"

///@cond DUPLICATE_MACRO
#ifdef ENGINECORE_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif
///@endcond

namespace Module
{
	namespace Tools
	{
		/**
		 * \brief Class that handle logs by type, level and display a log window
		 */
		class Logger : public Core::Interface::IModule
		{
		public:
			DECLARE_MODULE(S("Logger"))

			/**
			 * \brief Default constructor
			 */
			ENGINEDLL_API Logger() = default;
			/**
			 * \brief Default desctructor
			 */
			ENGINEDLL_API ~Logger() = default;

			/**
			 * \brief Create log entry
			 * \param _message Message of log
			 * \param _level Level of log
			 */
			ENGINEDLL_API void CreateEntry(Core::CoreType::String _message, ELog_level _level);

			/**
			 * \brief Clear all entries
			 */
			ENGINEDLL_API void ClearAllEntries();

		private:
			bool WriteLogs();

			std::vector<Log*> logs;

			std::ofstream outputFile;
		};
	}
}