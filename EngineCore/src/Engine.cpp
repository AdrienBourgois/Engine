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
		h_instance = _hInstance;

	parameters = new Utility::IniParser(".\\content\\Config\\config.ini");
	parameters->Parse();

	module_manager = new Core::Manager::ModuleManager();
	module_manager->InitializedModules();

	state = EEngineStates::Ready;
}

void Engine::Start()
{
	if (state == EEngineStates::Ready)
	{
		module_manager->StartModules();
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
		module_manager->UpdateModules();
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

	module_manager->Stop();
	delete module_manager;
	module_manager = nullptr;

	state = EEngineStates::Stopped;
}