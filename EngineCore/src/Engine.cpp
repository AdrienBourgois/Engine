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
	state = Initializing;

	if(_hInstance)
		h_instance = _hInstance;

	parameters = new Tools::IniParser(".\\content\\Config\\config.ini");
	parameters->Parse();

	module_manager = new ModuleManager();
	module_manager->InitializedModules();

	state = Ready;
}

void Engine::Start()
{
	if (state == Ready)
	{
		module_manager->StartModules();
		state = Starting;
	}

	if (state == Starting)
	{
		state = Running;
		Update();
	}
}

void Engine::Update()
{
	while (state == Running)
	{
		module_manager->UpdateModules();
	}
	if (state == AskToStop)
	{
		Destruct();
	}
}

void Engine::Stop()
{
	state = AskToStop;
}

void Engine::Destruct()
{
	state = Stopping;

	delete parameters;
	parameters = nullptr;

	module_manager->Stop();
	delete module_manager;
	module_manager = nullptr;

	state = Stopped;
}