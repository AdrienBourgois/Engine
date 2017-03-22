#pragma once

#include <vector>

#include "IModule.h"

#define WINDOW_MODULE 1
#define DIRECTX12WRAPPER_MODULE 2

class ModuleManager
{
public:
	ModuleManager();
	~ModuleManager();

	bool InitializedModules();
	bool StartModules();

	template<typename T>
	bool CreateModule(char* _name = nullptr);

	template<typename T>
	T* GetModule() const;
	template<typename T>
	T* GetModuleByName(char* _name) const;

	template<typename T>
	IModule* GetIModule() const;
	IModule* GetIModuleByName(char* _name) const;

	void UpdateModules();
	//void StopModule(char _module_type);
	void Stop();

private:
	std::vector<IModule*> modules;
};

template <typename T>
bool ModuleManager::CreateModule(char* _name)
{
	IModule* module;

	module = static_cast<IModule*>(new T);

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
T* ModuleManager::GetModule() const
{
	for (IModule* module : modules)
	{
		if (typeid(*module) == typeid(T))
			return static_cast<T*>(module);
	}

	return nullptr;
}

template<typename T>
T* ModuleManager::GetModuleByName(char* _name) const
{
	for (IModule* module : modules)
	{
		if (module->GetModuleName() == _name)
			return static_cast<T*>(module);
	}

	return nullptr;
}

template<typename T>
IModule* ModuleManager::GetIModule() const
{
	for (IModule* module : modules)
	{
		if (typeid(*module) == typeid(T))
			return module;
	}

	return nullptr;
}