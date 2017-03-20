#include "Core/ModuleManager.h"

#include "Display/Window.h"
#include "Render/DirectX/DirectX12Wrapper.h"

ModuleManager::ModuleManager()
{
}


ModuleManager::~ModuleManager()
{
}

void ModuleManager::CreateModule(char _module_type)
{
	IModule* module = nullptr;

	if (_module_type == WINDOW_MODULE)
		module = static_cast<IModule*>(new Display::Window());
	/*else if (_module_type == DIRECTX12WRAPPER_MODULE)
		DirectX12Wrapper* dx12 = new DirectX12Wrapper(nullptr);*/

	module->Initialize();

	modules.insert(std::make_pair(_module_type, module));
}

IModule* ModuleManager::GetModule(char _module_type)
{
	return modules[_module_type];
}

void ModuleManager::UpdateModules()
{
	for (auto module : modules)
	{
		module.second->Update();
	}
}

void ModuleManager::StopModule(char _module_type)
{
	modules[_module_type]->Destruct();
	modules.erase(_module_type);
}

void ModuleManager::Stop()
{
	for (auto module_pair : modules)
	{
		IModule* module = module_pair.second;
		module->Destruct();
		delete module;
		module = nullptr;
	}
}
