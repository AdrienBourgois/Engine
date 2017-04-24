#include "Logger.h"
#include <direct.h>

namespace Tools
{
	Logger::Logger()
	{
		CreateEntry(S("Logger Initialized !"), ELog_level::LOG_DEBUG);
		_mkdir("Logs");
		outputFile.open(".\\Logs\\Default.log", std::ios::app);
	}

	Logger::~Logger()
	{
		WriteLogs();
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

	bool Logger::WriteLogs()
	{
		if(outputFile.is_open())
		{
			for (Log* log : logs)
			{
				outputFile.write(log->GetCMessage(), log->GetMessage().SafeLength());
				outputFile.put('\n');
			}
			return true;
		}

		return false;
	}
}
