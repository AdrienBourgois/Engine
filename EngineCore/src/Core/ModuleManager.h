#pragma once

#include <map>

#include "Macros.h"

#include "IModule.h"

#define WINDOW_MODULE 1
#define DIRECTX12WRAPPER_MODULE 2

class ModuleManager
{
public:
	ModuleManager();
	~ModuleManager();

	void CreateModule(char _module_type);
	IModule* GetModule(char _module_type);
	void UpdateModules();
	void StopModule(char _module_type);
	void Stop();

private:
	std::map<char, IModule*> modules;
};

