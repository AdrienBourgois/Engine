#include "Engine.h"

BOOL APIENTRY DllMain(HINSTANCE _hinstDLL, DWORD _fdwReason, LPVOID _lpReserved )
{
	switch( _fdwReason )
	{
		case DLL_PROCESS_ATTACH:
			OutputDebugStringW(L"DllMain !");
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
	if(_hInstance)
		h_instance = _hInstance;

	parameters = new Tools::IniParser("config.ini");
	parameters->Parse();

	module_manager = new ModuleManager();

	module_manager->CreateModule(WINDOW_MODULE);

	running = true;
}

void Engine::Update() const
{
	while (running)
	{
		module_manager->UpdateModules();
	}
}

void Engine::Stop()
{
	module_manager->Stop();
	delete module_manager;

	running = false;
}
