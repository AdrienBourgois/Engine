#include "Core/Manager/ModuleManager.h"

#include "Modules/Display/Window.h"
#include "Modules/Render/RenderInterface.h"

bool Core::Manager::ModuleManager::InitializeModules()
{
	if (!CreateModule<Module::Display::Window>(S("Window")))
		return false;
	if (!CreateModule<Module::Render::RenderInterface>(S("RenderInterface")))
		return false;
	if (!CreateModule<Module::Tools::Logger>(S("Logger")))
		return false;

	return true;
}

bool Core::Manager::ModuleManager::StartModules()
{
	for (Interface::IModule* module : modules)
	{
		if (!module->Start())
			return false;
	}

	return true;
}

Core::Interface::IModule* Core::Manager::ModuleManager::GetIModuleByName(char* _name) const
{
	for (Interface::IModule* module : modules)
	{
		if (module->GetModuleName() == _name)
			return module;
	}

	return nullptr;
}

void Core::Manager::ModuleManager::UpdateModules()
{
	for (Interface::IModule* module : modules)
	{
		module->Update();
	}
}


void Core::Manager::ModuleManager::Stop()
{
	for (Interface::IModule* module : modules)
	{
		module->Destruct();
		delete module;
	}
}