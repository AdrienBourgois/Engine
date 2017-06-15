#include <Windows.h>

#include "Modules/Tools/Logs/Logger.h"

#define FILE_NON_EXISTANT 0xFFFFFFFF

bool Module::Tools::Logs::Logger::Initialize()
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

bool Module::Tools::Logs::Logger::Start()
{
	return true;
}

bool Module::Tools::Logs::Logger::Update()
{
	return true;
}

bool Module::Tools::Logs::Logger::Destruct()
{
	WriteLogs();
	ClearAllEntries();

	return true;
}

void Module::Tools::Logs::Logger::CreateEntry(Core::CoreType::String _message, ELog_level _level)
{
	Log* log = new Log(_message, _level);
	logs.push_back(log);
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
			outputFile.write(log->GetCMessage(), log->GetStringMessage().SafeLength());
			outputFile.put('\n');
		}
		return true;
	}

	return false;
}