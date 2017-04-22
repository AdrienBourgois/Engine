#pragma once

#include <vector>
#include <fstream>

#include "Tools/Logger/Log.h"

///@cond DUPLICATE_MACRO
#ifdef ENGINECORE_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif
///@endcond

namespace Tools
{
	/**
	 * \brief Class that handle logs by type, level and display a log window
	 */
	class Logger
	{
	public:
		/**
		 * \brief Classic constructor (open file)
		 */
		ENGINEDLL_API Logger();
		/**
		 * \brief Save logs in file then destruct
		 */
		ENGINEDLL_API ~Logger();

		/**
		 * \brief Return an instance of the logger singleton
		 * \return Instance of logger
		 */
		static Logger* GetInstance()
		{
			static Logger instance;
			return &instance;
		}

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

		std::vector<Tools::Log*> logs;

		std::ofstream outputFile;
	};
}
