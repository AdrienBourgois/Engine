#include "Engine.h"

Engine* Engine::instance = nullptr;

BOOL WINAPI DllMain(const HINSTANCE _hinst_dll, const DWORD _fdw_reason, LPVOID _lp_reserved )
{
	switch( _fdw_reason )
	{
		case DLL_PROCESS_ATTACH:
			Engine::GetInstance()->SetHInstance(_hinst_dll);
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			Engine::GetInstance()->Stop();
			break;

		default: return false;
	}

	return true;
}

void Engine::Initialize(const HINSTANCE _h_instance)
{
	state = EEngineStates::Initializing;

	if(_h_instance)
		hInstance = _h_instance;

	parameters = new Utility::IniParser(".\\content\\Config\\config.ini");
	parameters->Parse();

	scriptManager = new Core::Manager::ScriptManager();

	moduleManager = new Core::Manager::ModuleManager();
	moduleManager->InitializeModules();

	state = EEngineStates::Ready;
}

void Engine::Start()
{
	if (state == EEngineStates::Ready)
	{
		moduleManager->StartModules();
		scriptManager->StartScripts();
		state = EEngineStates::Starting;
	}

	if (state == EEngineStates::Starting)
	{
		state = EEngineStates::Running;
		Update();
	}
}

void Engine::Update()
{
	while (state == EEngineStates::Running)
	{
		scriptManager->UpdateScripts();
		moduleManager->UpdateModules();
	}
	if (state == EEngineStates::AskToStop)
	{
		Destruct();
	}
}

void Engine::Stop()
{
	state = EEngineStates::AskToStop;
}

void Engine::Destruct()
{
	state = EEngineStates::Stopping;

	delete parameters;
	parameters = nullptr;

	scriptManager->Stop();
	delete scriptManager;
	scriptManager = nullptr;

	moduleManager->Stop();
	delete moduleManager;
	moduleManager = nullptr;

	state = EEngineStates::Stopped;
}
