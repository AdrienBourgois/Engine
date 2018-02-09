#pragma once

#include "Engine.h"

#include "Core/Interface/IModule.h"
#include "Core/Interface/IKeyboardInputs.h"
#include "Core/Interface/IMouseInputs.h"

namespace Module
{
	/**
	 * \brief Process inputs from system
	 */
	namespace Inputs
	{
		/**
		 * \brief List of API for keyboard inputs
		 */
		enum class KeyboardInputsApi
		{
			Windows,
		};

		/**
		 * \brief List of API for mouse inputs
		 */
		enum class MouseInputsApi
		{
			Windows,
		};

		/**
		 * \brief Handle inputs from keyboard and mouse
		 */
		class ENGINEDLL_API Input : public Core::Interface::IModule
		{
		public:
			DECLARE_MODULE(S("Input"))

			/**
			 * \brief Default constructor
			 */
			Input() = default;
			/**
			 * \brief Destructor
			 */
			~Input();

			/**
			 * \brief Create a wrapper for keyboard inputs
			 * \param _api API to use
			 * \return Pointer to the wrapper
			 */
			Core::Interface::IKeyboardInputs* CreateKeyboardInputsWrapper(KeyboardInputsApi _api);
			/**
			 * \brief Create a wrapper for mouse inputs
			 * \param _api API to use
			 * \return Pointer to the wrapper
			 */
			Core::Interface::IMouseInputs* CreateMouseInputsWrapper(MouseInputsApi _api);
			/**
			 * \brief Return instance of the wrapper for keyboard inputs
			 * \return Pointer to the wrapper
			 */
			Core::Interface::IKeyboardInputs* GetKeyboardInputsWrapper() const;
			/**
			 * \brief Return instance of the wrapper for mouse inputs
			 * \return Pointer to the wrapper
			 */
			Core::Interface::IMouseInputs* GetMouseInputsWrapper() const;

		private:
			/**
			 * \brief Pointer to the keyboard input wrapper
			 */
			Core::Interface::IKeyboardInputs* keyboardInputsWrapper = nullptr;
			/**
			 * \brief Pointer to the mouse input wrapper
			 */
			Core::Interface::IMouseInputs* mouseInputsWrapper = nullptr;
		};
	}
}

