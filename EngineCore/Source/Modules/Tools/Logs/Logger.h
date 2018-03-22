#pragma once

#include <vector>
#include <fstream>

#include "Modules/Tools/Logs/Log.h"
#include "Core/Interface/IModule.h"
#include "Core/CoreType/Container/Vector.h"

namespace Module
{
	/**
	 * \brief Utility modules
	 */
	namespace Tools
	{
		/**
		 * \brief Logger and Log classes
		 */
		namespace Logs
		{
			/**
			 * \brief Class that handle logs by type, level and display a log window
			 */
			class Logger : public Core::Interface::IModule
			{
			public:
				DECLARE_MODULE(S("Logger"))

				/**
				 * \brief Constructor
				 */
				ENGINEDLL_API Logger();
				/**
				 * \brief Default destructor
				 */
				ENGINEDLL_API ~Logger() = default;

				/**
				 * \brief Create log entry
				 * \param _message Message of log
				 * \param _level Level of log
				 */
				ENGINEDLL_API void CreateEntry(const Core::CoreType::String& _message, ELog_level _level);

				/**
				 * \brief Create log entry with source file
				 * \param _message Message of log
				 * \param _level Level of log
				 * \param _file File caller of this function
				 * \param _line Line number of file call of this function
				 */
				ENGINEDLL_API void CreateEntry(const Core::CoreType::String& _message, ELog_level _level, const Core::CoreType::String& _file, int _line);

				/**
				 * \brief Clear all entries
				 */
				ENGINEDLL_API void ClearAllEntries();

			private:
				/**
				 * \brief Create a new Windows Console Prompt and bind it to standard outputs
				 */
				static void CreateWindowsConsole();
				/**
				 * \brief Write all entries in file
				 * \return Is function a success
				 */
				bool WriteLogs();
				/**
				 * \brief Write single entry in file
				 * \return Is function a success
				 */
				bool WriteLog(Log* _log);

				/**
				 * \brief Store entries
				 */
				Core::CoreType::Container::Vector<Log*> logs;

				/**
				 * \brief Stream to output file
				 */
				std::ofstream outputFile;
			};
		}
	}
}
