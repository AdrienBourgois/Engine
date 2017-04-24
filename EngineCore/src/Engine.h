#pragma once

#include <Windows.h>

#include "Macros.h"

#include "Utility/Ini/IniParser.h"
#include "Core/Manager/ModuleManager.h"

enum class EEngineStates : int
{
	Off = 0,
	Initializing,
	Ready,
	Starting,
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

	template<typename T>
	T* GetModule() const;

	const Utility::IniParser* GetParameters() const { return parameters; }

	EEngineStates GetState() const { return state; }

private:
	Engine() = default;
	~Engine() = default;

	Utility::IniParser* parameters = nullptr;

	Core::Manager::ModuleManager* module_manager = nullptr;

	HINSTANCE h_instance = nullptr;

	EEngineStates state = EEngineStates::Off;
};

template <typename T>
T* Engine::GetModule() const
{
	return module_manager->GetModule<T>();
}