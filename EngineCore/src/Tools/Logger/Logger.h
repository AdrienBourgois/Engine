﻿#pragma once

#include <vector>
#include "Macros.h"
#include "Tools/Logger/Log.h"

namespace Tools
{
	/**
	 * \brief Class that handle logs by type, level and display a log window
	 */
	class Logger
	{
	public:
		ENGINEDLL_API Logger();
		ENGINEDLL_API ~Logger();

		/**
		 * \brief Create log entry
		 * \param _message Message of log
		 * \param _level Lvel of log
		 */
		ENGINEDLL_API void CreateEntry(Core::CoreType::String _message, ELog_level _level);

		/**
		 * \brief Clear all entries
		 */
		ENGINEDLL_API void ClearAllEntries();

	private:
		std::vector<Tools::Log*> logs;
	};
}
