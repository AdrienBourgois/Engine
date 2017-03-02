#pragma once

#ifdef ENGINECORE_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif

#include <vector>
#include "Log.h"

namespace Tools
{
	/**
	 * \brief Class that handle logs by type, level and display a log window
	 */
	class Logger
	{
	public:
		Logger();
		~Logger();

		/**
		 * \brief Create log entry
		 * \param _message Message of log
		 */
		void CreateEntry(char* _message, ELog_level _level);

		/**
		 * \brief Clear all entries
		 */
		void ClearAllEntries();

	private:
		std::vector<Tools::Log*> logs;
	};
}
