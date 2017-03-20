#pragma once

#include <Windows.h>

#include "macros.h"

#include "Tools/Ini/IniParser.h"
#include "Core/ModuleManager.h"

enum EEngineStates
{
	Off = 0,
	Initializing,
	Ready,
	Running,
	AskToStop,
	Stopping,
	Stopped
};

class ENGINEDLL_API Engine
{
public:
	Engine(Engine const&) = delete;
	void operator=(Engine const&) = delete;

	static Engine* GetInstance()
	{
		static Engine instance;
		return &instance;
	}

	void Initialize(HINSTANCE hInstance = nullptr);
	void Start();
	void Update();
	void Stop();
	void Destruct();

	void SetHInstance(HINSTANCE _hInstance) { h_instance = _hInstance; }
	HINSTANCE GetHInstance() const { return h_instance; }
	IModule* GetModule(char module) const { return module_manager->GetModule(module); }

	const Tools::IniParser* GetParameters() const { return parameters; }

	EEngineStates GetState() const { return state; }

private:
	Engine() = default;
	~Engine() = default;

	Tools::IniParser* parameters = nullptr;

	ModuleManager* module_manager = nullptr;

	HINSTANCE h_instance = nullptr;

	EEngineStates state = Off;
};

