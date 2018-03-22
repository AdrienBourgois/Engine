#include <Windows.h>

#include "Modules/Tools/Logs/Logger.h"
#include <iostream>
#include <fcntl.h>
#include <io.h>

#define FILE_NON_EXISTANT 0xFFFFFFFF

Module::Tools::Logs::Logger::Logger()
{
	if (GetFileAttributes(L".\\Logs\\Default.log") != FILE_NON_EXISTANT)
	{
		if (GetFileAttributes(L".\\Logs\\Previous.log") != FILE_NON_EXISTANT)
			DeleteFile(L".\\Logs\\Previous.log");
		MoveFile(L".\\Logs\\Default.log", L".\\Logs\\Previous.log");
	}
	else
		CreateDirectory(L"Logs", nullptr);

	outputFile.open(".\\Logs\\Default.log");

	CreateWindowsConsole();

	CreateEntry(S("Logger Initialized !"), ELog_level::LOG_DEBUG);
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

void Module::Tools::Logs::Logger::CreateEntry(const Core::CoreType::String& _message, const ELog_level _level)
{
	Log* log = new Log(_message, _level);
	logs.PushBack(log);
	std::cout << log->GetStructuredLog().CStr() << std::endl << std::endl;
	WriteLog(log);
}

void Module::Tools::Logs::Logger::CreateEntry(const Core::CoreType::String& _message, const ELog_level _level, const Core::CoreType::String& _file, const int _line)
{
	Log* log = new Log(_message, _level, _file, _line);
	logs.PushBack(log);
	std::cout << log->GetStructuredLog().CStr() << std::endl << std::endl;
	WriteLog(log);
}

void Module::Tools::Logs::Logger::ClearAllEntries()
{
	for (Log* log : logs) { delete log; }
	logs.Clear();
}

void Module::Tools::Logs::Logger::CreateWindowsConsole()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	HANDLE console_output = GetStdHandle(STD_OUTPUT_HANDLE);
	const int system_output = _open_osfhandle(intptr_t(console_output), _O_TEXT);
	FILE *c_output_handle = _fdopen(system_output, "w");

	HANDLE console_error = GetStdHandle(STD_ERROR_HANDLE);
	const int system_error = _open_osfhandle(intptr_t(console_error), _O_TEXT);
	FILE *c_error_handle = _fdopen(system_error, "w");

	HANDLE console_input = GetStdHandle(STD_INPUT_HANDLE);
	const int system_input = _open_osfhandle(intptr_t(console_input), _O_TEXT);
	FILE *c_input_handle = _fdopen(system_input, "r");

	freopen_s(&c_input_handle, "CONIN$", "r", stdin);
	freopen_s(&c_output_handle, "CONOUT$", "w", stdout);
	freopen_s(&c_error_handle, "CONOUT$", "w", stderr);

	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

	std::cout << "Windows Console Created and Initialized !" << std::endl;
}

bool Module::Tools::Logs::Logger::WriteLogs()
{
	if (outputFile.is_open())
	{
		for (Log* log : logs)
		{
			WriteLog(log);
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
		Core::CoreType::String fancy_log = _log->GetStructuredLog();
		outputFile.write(fancy_log.CStr(), fancy_log.SafeLength());
		outputFile.put('\n');

		return true;
	}

	return false;
}
