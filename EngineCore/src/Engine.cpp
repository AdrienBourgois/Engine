#include "Engine.h"

BOOL WINAPI DllMain(HINSTANCE _hinstDLL, DWORD _fdwReason, LPVOID _lpReserved )
{
	switch( _fdwReason )
	{
		case DLL_PROCESS_ATTACH:
			Engine::GetInstance()->SetHInstance(_hinstDLL);
			Engine::GetInstance()->Initialize();
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

void Engine::Initialize(HINSTANCE _hInstance)
{
	state = EEngineStates::Initializing;

	if(_hInstance)
		hInstance = _hInstance;

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
