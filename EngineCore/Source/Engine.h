#pragma once

#include <Windows.h>

#include "Macros.h"

#include "Utility/Ini/IniParser.h"
#include "Core/Manager/ModuleManager.h"
#include "Core/Manager/ScriptManager.h"

/**
 * \brief Engine (base class of engine)
 */
class ENGINEDLL_API Engine
{
public:
	/**
	 * \brief Delete copy constructor
	 */
	Engine(Engine const&) = delete;
	/**
	 * \brief Delete operator =
	 */
	void operator=(Engine const&) = delete;

	/**
	 * \brief Handle and return singleton of engine class
	 * \return Instance of the engine
	 */
	static Engine* GetInstance()
	{
		if (!instance)
			instance = new Engine();
		return instance;
	}

	/**
	 * \brief Initialize the engine
	 * \param hInstance Handle Instance of a parent
	 */
	void Initialize(HINSTANCE hInstance = nullptr);
	/**
	 * \brief Start the engine (and components, scripts...)
	 */
	void Start();
	/**
	 * \brief Update the engine (and components, scripts...)
	 */
	void Update();
	/**
	 * \brief Stop the engine (and components, scripts...)
	 */
	void Stop();
	/**
	 * \brief Destruct the engine (and components, scripts...)
	 */
	void Destruct();

	/**
	 * \brief Set a new hInstance
	 * \param _hInstance New instance
	 */
	void SetHInstance(HINSTANCE _hInstance) { hInstance = _hInstance; }
	/**
	 * \brief Return the hInstance
	 * \return Instance
	 */
	HINSTANCE GetHInstance() const { return hInstance; }

	/**
	 * \brief Get a module by his type
	 * \tparam T Type of module
	 * \return Pointer to the module
	 */
	template<typename T>
	T* GetModule() const;

	/**
	 * \brief Get parameters handle
	 * \return Pointer to the IniParser
	 */
	const Utility::IniParser* GetParameters() const { return parameters; }

	/**
	 * \brief Add a script to the engine
	 * \tparam T Type of the script
	 * \tparam U Ensure that the script inherit from Core::Interface::IScript
	 */
	template <typename T, class U = typename std::enable_if<std::is_base_of<Core::Interface::IScript, T>::value, T>::type>
	const void AddScript() const;

	/**
	 * \brief List of engine states
	 */
	enum class EEngineStates : int
	{
		/**
		 * \brief Off
		 */
		Off = 0,
		/**
		 * \brief Initialize engine, modules, scripts...
		 */
		Initializing,
		/**
		 * \brief Ready to call the Start method
		 */
		Ready,
		/**
		 * \brief Start  engine, modules, scripts...
		 */
		Starting,
		/**
		 * \brief Engine currently running (block in Update method)
		 */
		Running,
		/**
		 * \brief An script, module, ... (or the engine himself) ask to stop the engine
		 */
		AskToStop,
		/**
		 * \brief Currently stop all parts of engine
		 */
		Stopping,
		/**
		 * \brief Engine stopped, nothing running
		 */
		Stopped
	};

	/**
	 * \brief Get the current state of the engine
	 * \return Current state
	 */
	EEngineStates GetState() const { return state; }

private:
	/**
	 * \brief Default constructor
	 */
	Engine() = default;
	/**
	 * \brief Default destructor
	 */
	~Engine() = default;

	/**
	 * \brief Handle parameters class
	 */
	Utility::IniParser* parameters = nullptr;

	/**
	 * \brief Handle all modules
	 */
	Core::Manager::ModuleManager* moduleManager = nullptr;
	/**
	 * \brief Handle all scripts
	 */
	Core::Manager::ScriptManager* scriptManager = nullptr;

	/**
	 * \brief Store hInstance
	 */
	HINSTANCE hInstance = nullptr;

	/**
	 * \brief Store current engine state
	 */
	EEngineStates state = EEngineStates::Off;

	/**
	 * \brief Singleton instance of Engine Class
	 */
	static Engine* instance;
};

template <typename T>
T* Engine::GetModule() const
{
	return moduleManager->GetModule<T>();
}

template <typename T, class U>
const void Engine::AddScript() const
{
	scriptManager->AddScript<U>();
}

/**
 * \brief Core classes
 */
namespace Core
{
	/**
	 * \brief Types for all engine, modules and scripts
	 */
	namespace CoreType{}
	/**
	 * \brief Interface for modules and scripts
	 */
	namespace Interface{}
	/**
	 * \brief Managers to handle modules, scripts, ...
	 */
	namespace Manager{}
}

/**
 * \brief Maths utility classes
 */
namespace Math{}

/**
 * \brief Services classes
 */
namespace Module{}

/**
 * \brief GameObjects and components
 */
namespace Object{}

/**
 * \brief Scripts classes
 */
namespace Scripts{}

/**
 * \brief Utility classes
 */
namespace Utility{}