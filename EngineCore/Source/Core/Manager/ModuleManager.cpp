#include "Core/Manager/ModuleManager.h"

#include "Modules/Display/Window.h"
#include "Modules/Render/RenderInterface.h"
#include "Modules/Inputs/Input.h"
#include "Modules/Time/Clock.h"

Core::Manager::ModuleManager::ModuleManager(Engine* _engine_reference) : engine(_engine_reference)
{
}

bool Core::Manager::ModuleManager::InitializeModules()
{
	if (!CreateModule<Module::Time::Clock>(S("Clock")))
		return false;
	if (!CreateModule<Module::Tools::Logs::Logger>(S("Logger")))
		return false;
	if (!CreateModule<Module::Inputs::Input>(S("Input")))
		return false;
	if (!CreateModule<Module::Display::Window>(S("Window")))
		return false;
	if (!CreateModule<Module::Render::RenderInterface>(S("RenderInterface")))
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

void Core::Manager::ModuleManager::UpdateModules()
{
	for (Interface::IModule* module : modules)
	{
		module->Update();
	}
}


void Core::Manager::ModuleManager::Stop()
{
	const Module::Time::Clock* clock = Engine::GetInstance()->GetModule<Module::Time::Clock>();
	LOG(S("Average FPS : ") + SN(clock->GetFpsAverage()) + S(" - Total time : ") + clock->GetTotalTime().ToString(), LOG_INFO);

	for (Interface::IModule* module : modules)
	{
		module->Destruct();
		delete module;
	}
}