#pragma once

#include <Windows.h>

#include "Macros.h"

#include "Utility/Ini/IniParser.h"
#include "Core/Manager/ModuleManager.h"
#include "Core/Manager/ScriptManager.h"

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

	void SetHInstance(HINSTANCE _hInstance) { hInstance = _hInstance; }
	HINSTANCE GetHInstance() const { return hInstance; }

	template<typename T>
	T* GetModule() const;

	const Utility::IniParser* GetParameters() const { return parameters; }

	template <typename T = Core::Interface::IScript>
	const void AddScript() const;

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

	EEngineStates GetState() const { return state; }

private:
	Engine() = default;
	~Engine() = default;

	Utility::IniParser* parameters = nullptr;

	Core::Manager::ModuleManager* moduleManager = nullptr;
	Core::Manager::ScriptManager* scriptManager = nullptr;

	HINSTANCE hInstance = nullptr;

	EEngineStates state = EEngineStates::Off;
};

template <typename T>
T* Engine::GetModule() const
{
	return moduleManager->GetModule<T>();
}

template <typename T>
const void Engine::AddScript() const
{
	scriptManager->AddScript<T>();
}