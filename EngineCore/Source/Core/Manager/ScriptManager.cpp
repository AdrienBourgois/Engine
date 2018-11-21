#include "Engine.h"

#include "Core/Manager/ScriptManager.h"
#include "Modules/Time/Clock.h"

bool Core::Manager::ScriptManager::StartScripts()
{
	while (!scriptsToStart.empty())
	{
		scriptsToStart.front()->Start();
		scriptsToStart.pop();
	}

	return true;
}

Core::Interface::IScript* Core::Manager::ScriptManager::GetIScriptByName(const CoreType::String& _name) const
{
	for (Interface::IScript* script : scripts)
	{
		if (script->GetScriptName() == _name)
			return script;
	}

	return nullptr;
}

void Core::Manager::ScriptManager::UpdateScripts()
{
	StartScripts();

	Module::Time::Clock* clock = Engine::GetInstance()->GetModule<Module::Time::Clock>();

	for (Interface::IScript* script : scripts)
	{
		script->Update();
		script->Update(clock->GetDeltaTime());
	}
}

void Core::Manager::ScriptManager::Stop()
{
	std::queue<Interface::IScript*>().swap(scriptsToStart);

	for (Interface::IScript* script : scripts)
	{
		script->Destruct();
		delete script;
	}
}