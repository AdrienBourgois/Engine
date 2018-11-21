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
	state = EEngineState::Initializing;

	if(_h_instance)
		hInstance = _h_instance;

	parameters = new Utility::IniParser(".\\content\\Config\\config.ini");
	parameters->Parse();

	scriptManager = new Core::Manager::ScriptManager();

	moduleManager = new Core::Manager::ModuleManager(this);
	moduleManager->InitializeModules();

	state = EEngineState::Ready;
}

void Engine::Start()
{
	if (state == EEngineState::Ready)
	{
		moduleManager->StartModules();
		scriptManager->StartScripts();
		state = EEngineState::Starting;
	}

	if (state == EEngineState::Starting)
	{
		state = EEngineState::Running;
		Update();
	}
}

void Engine::Update()
{
	while (state == EEngineState::Running)
	{
		scriptManager->UpdateScripts();
		moduleManager->UpdateModules();
	}
	if (state == EEngineState::AskToStop)
	{
		Destruct();
	}
}

void Engine::Stop()
{
	state = EEngineState::AskToStop;
}

void Engine::Destruct()
{
	state = EEngineState::Stopping;

	delete parameters;
	parameters = nullptr;

	scriptManager->Stop();
	delete scriptManager;
	scriptManager = nullptr;

	moduleManager->Stop();
	delete moduleManager;
	moduleManager = nullptr;

	state = EEngineState::Stopped;
}