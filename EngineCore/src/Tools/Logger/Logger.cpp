﻿#include "Logger.h"

namespace Tools
{
	Logger::Logger()
	{
		CreateEntry(S("Logger Initialized !"), INFO);
	}

	Logger::~Logger()
	{
		ClearAllEntries();
	}

	void Logger::CreateEntry(Core::CoreType::String _message, ELog_level _level)
	{
		Log* log = new Log(_message, _level);
		logs.push_back(log);
	}

	void Logger::ClearAllEntries()
	{
		for (Log* log : logs) { delete log; }
		logs.clear();
	}
}
