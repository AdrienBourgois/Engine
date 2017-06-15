#include "Core/Manager/ScriptManager.h"
#include "Modules/Time/Clock.h"

bool Core::Manager::ScriptManager::StartScripts()
{
	while (scriptsToStart.size())
	{
		scriptsToStart.front()->Start();
		scriptsToStart.pop();
	}

	return true;
}

Core::Interface::IScript* Core::Manager::ScriptManager::GetIScriptByName(CoreType::String _name) const
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

	for (Interface::IScript* script : scripts)
	{
		script->Update();
		script->Update(MODULE(Module::Time::Clock)->GetDeltaTime());
	}
}

void Core::Manager::ScriptManager::Stop()
{
	scriptsToStart.empty();

	for (Interface::IScript* script : scripts)
	{
		script->Destruct();
		delete script;
	}
}