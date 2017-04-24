#include "Logger.h"
#include <Windows.h>

#define FILE_NON_EXISTANT 0xFFFFFFFF
namespace Module
{
	namespace Tools
	{
		bool Logger::Initialize()
		{
			CreateEntry(S("Logger Initialized !"), ELog_level::LOG_DEBUG);
			if (GetFileAttributes(L".\\Logs\\Default.log") != FILE_NON_EXISTANT)
			{
				if (GetFileAttributes(L".\\Logs\\Previous.log") != FILE_NON_EXISTANT)
					DeleteFile(L".\\Logs\\Previous.log");
				MoveFile(L".\\Logs\\Default.log", L".\\Logs\\Previous.log");
			}
			else
				CreateDirectory(L"Logs", nullptr);

			outputFile.open(".\\Logs\\Default.log");

			return true;
		}

		bool Logger::Start()
		{
			return true;
		}

		bool Logger::Update()
		{
			return true;
		}

		bool Logger::Destruct()
		{
			WriteLogs();
			ClearAllEntries();

			return true;
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
			if (outputFile.is_open())
			{
				for (Log* log : logs)
				{
					outputFile.write(log->GetCMessage(), log->GetStringMessage().SafeLength());
					outputFile.put('\n');
				}
				return true;
			}

			return false;
		}
	}
}