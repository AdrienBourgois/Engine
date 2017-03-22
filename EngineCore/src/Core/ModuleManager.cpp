#include "Core/ModuleManager.h"

#include "Display/Window.h"
#include "Render/DirectX/DirectX12Wrapper.h"

ModuleManager::ModuleManager()
{}

ModuleManager::~ModuleManager()
{}

bool ModuleManager::InitializedModules()
{
	if (!CreateModule<Display::Window>(S("Window")))
		return false;
	if (!CreateModule<DirectX12Wrapper>(S("DX12")))
		return false;

	return true;
}

bool ModuleManager::StartModules()
{
	for (IModule* module : modules)
	{
		if (!module->Start())
			return false;
	}

	return true;
}

IModule* ModuleManager::GetIModuleByName(char* _name) const
{
	for (IModule* module : modules)
	{
		if (module->GetModuleName() == _name)
			return module;
	}

	return nullptr;
}

void ModuleManager::UpdateModules()
{
	for (IModule* module : modules)
	{
		module->Update();
	}
}

/*void ModuleManager::StopModule(char _module_type)
{
	modules[_module_type]->Destruct();
	modules.erase(_module_type);
}*/

void ModuleManager::Stop()
{
	for (IModule* module : modules)
	{
		module->Destruct();
		delete module;
	}
}