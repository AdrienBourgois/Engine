#pragma once

#include "Engine.h"

#include "Core/Interface/IModule.h"
#include "Core/Interface/IKeyboardInputs.h"

namespace Module
{
	enum class KeyboardInputsApi
	{
		Windows,
	};

	enum class MouseInputsApi
	{
		Windows,
	};

	class ENGINEDLL_API Inputs : public Core::Interface::IModule
	{
	public:
		DECLARE_MODULE(S("Inputs"))

		Inputs() = default;
		~Inputs();

		Core::CoreType::Interface::IKeyboardInputs* CreateKeyboardInputsWrapper(KeyboardInputsApi _api);
		Core::CoreType::Interface::IKeyboardInputs* GetKeyboardInputsWrapper() const;
		Core::CoreType::Interface::IKeyboardInputs* Keyboard() const;

	private:
		Core::CoreType::Interface::IKeyboardInputs* keyboardInputsWrapper = nullptr;
	};
}

