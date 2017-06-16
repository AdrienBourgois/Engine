#pragma once

#include "Core/Interface/IScript.h"
#include "Modules/Time/Clock.h"
#include "Modules/Display/Window.h"
#include "Modules/Render/RenderInterface.h"
#include "Modules/Inputs/Input.h"

using namespace Core;
using namespace CoreType;

/**
 * \brief Get current delta time
 */
#define DeltaTime getClock()->GetDeltaTime()
/**
 * \brief Get keyboard inputs
 */
#define Keyboard getInputs()->GetKeyboardInputsWrapper()
/**
 * \brief Get active camera
 */
#define Camera getRenderInterface()->GetActiveCamera()

namespace Scripts
{
	/**
	 * \brief Simple script class
	 * \note Inherit your scripts from this class, or childs of this class
	 */
	class ENGINEDLL_API Script : public Interface::IScript
	{
	public:
		/**
		 * \brief Constructor
		 */
		Script();
		/**
		 * \brief Default destructor
		 */
		~Script() = default;

		/**
		 * \brief Return clock module
		 * \return Clock module
		 */
		Module::Time::Clock* getClock() const;
		/**
		 * \brief Return window module
		 * \return Window module
		 */
		Module::Display::Window* getWindow() const;
		/**
		 * \brief Return render interface module
		 * \return RenderInterface module
		 */
		Module::Render::RenderInterface* getRenderInterface() const;
		/**
		 * \brief Return logger module
		 * \return Logger module
		 */
		Module::Tools::Logs::Logger* getLogger() const;
		/**
		 * \brief Return inputs module
		 * \return Inputs module
		 */
		Module::Inputs::Input* getInputs() const;

	private:
		/**
		 * \brief Store a pointer to the clock module
		 */
		Module::Time::Clock* clockModuleReference = nullptr;
		/**
		 * \brief Store a pointer to the window module
		 */
		Module::Display::Window* windowModuleReference = nullptr;
		/**
		 * \brief Store a pointer to the render interface module
		 */
		Module::Render::RenderInterface* renderInterfaceModuleReference = nullptr;
		/**
		 * \brief Store a pointer to the logger module
		 */
		Module::Tools::Logs::Logger* loggerModuleReference = nullptr;
		/**
		 * \brief Store a pointer to the inputs module
		 */
		Module::Inputs::Input* inputsModuleReference = nullptr;
	};
}
