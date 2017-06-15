#pragma once

#include <vector>
#include <fstream>

#include "Modules/Tools/Logs/Log.h"
#include "Core/Interface/IModule.h"

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
				/**
				 * \brief Write entries in file
				 * \return Is function a success
				 */
				bool WriteLogs();

				/**
			 * \brief Store entries
			 */
				std::vector<Log*> logs;

				/**
				 * \brief Stream to output file
				 */
				std::ofstream outputFile;
			};
		}
	}
}