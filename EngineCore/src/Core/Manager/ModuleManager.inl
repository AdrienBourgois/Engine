#pragma once

template <typename T>
bool Core::Manager::ModuleManager::CreateModule(CoreType::String _name)
{
	Interface::IModule * module = static_cast<Interface::IModule*>(new T);

	if (module)
	{
		if (!_name)
			module->SetDefaultModuleName();
		else
			module->SetModuleName(_name);

		module->Initialize();

		modules.push_back(module);
		return true;
	}

	return false;
}

template<typename T>
T* Core::Manager::ModuleManager::GetModule() const
{
	for (Interface::IModule* module : modules)
	{
		if (typeid(*module) == typeid(T))
			return static_cast<T*>(module);
	}

	return nullptr;
}

template<typename T>
T* Core::Manager::ModuleManager::GetModuleByName(CoreType::String _name) const
{
	for (Interface::IModule* module : modules)
	{
		if (module->GetModuleName() == _name)
			return static_cast<T*>(module);
	}

	return nullptr;
}

template<typename T>
Core::Interface::IModule* Core::Manager::ModuleManager::GetIModule() const
{
	for (Interface::IModule* module : modules)
	{
		if (typeid(*module) == typeid(T))
			return module;
	}

	return nullptr;
}