#pragma once

#include "Core/Interface/IScript.h"

template <typename T>
bool Core::Manager::ScriptManager::AddScript()
{
	Interface::IScript * script = static_cast<Interface::IScript*>(new T);

	script->Initialize();

	scriptsToStart.push(script);
	scripts.push_back(script);

	return true;
}

template<typename T>
T* Core::Manager::ScriptManager::GetScriptByName(CoreType::String _name) const
{
	for (Interface::IScript* script : scripts)
	{
		if (script->GetScriptName() == _name)
			return static_cast<T*>(script);
	}

	return nullptr;
}