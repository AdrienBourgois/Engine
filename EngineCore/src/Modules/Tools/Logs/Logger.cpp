#include <Windows.h>

#include "Modules/Tools/Logs/Logger.h"

#define FILE_NON_EXISTANT 0xFFFFFFFF

Module::Tools::Logs::Logger::Logger()
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
}

bool Module::Tools::Logs::Logger::Initialize()
{
	return true;
}

bool Module::Tools::Logs::Logger::Start()
{
	WriteLogs();
	return true;
}

bool Module::Tools::Logs::Logger::Update()
{
	return true;
}

bool Module::Tools::Logs::Logger::Destruct()
{
	ClearAllEntries();

	return true;
}

void Module::Tools::Logs::Logger::CreateEntry(Core::CoreType::String _message, ELog_level _level)
{
	Log* log = new Log(_message, _level);
	logs.push_back(log);
	WriteLog(log);
}

void Module::Tools::Logs::Logger::ClearAllEntries()
{
	for (Log* log : logs) { delete log; }
	logs.clear();
}

bool Module::Tools::Logs::Logger::WriteLogs()
{
	if (outputFile.is_open())
	{
		for (Log* log : logs)
		{
			Core::CoreType::String time_string = log->GetTime().ToString();
			outputFile.write(time_string.CStr(), time_string.Length());
			outputFile.write(" = ", 3);
			outputFile.write(log->GetCMessage(), log->GetStringMessage().Length());
			outputFile.put('\n');
			outputFile.flush();
		}
		return true;
	}

	return false;
}

bool Module::Tools::Logs::Logger::WriteLog(Log* _log)
{
	if (outputFile.is_open())
	{
		Core::CoreType::String time_string = _log->GetTime().ToString();
		outputFile.write(time_string.CStr(), time_string.Length());
		outputFile.write(" = ", 3);
		outputFile.write(_log->GetCMessage(), _log->GetStringMessage().Length());
		outputFile.put('\n');

		return true;
	}

	return false;
}
