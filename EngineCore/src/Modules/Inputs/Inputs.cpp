#include "Inputs.h"
#include "WindowsKeyboard.h"

Module::Inputs::~Inputs()
{
	delete keyboardInputsWrapper;
}

Core::CoreType::Interface::IKeyboardInputs* Module::Inputs::CreateKeyboardInputsWrapper(KeyboardInputsApi _api)
{
	if (_api == KeyboardInputsApi::Windows)
		keyboardInputsWrapper = new WindowsKeyboard;

	return keyboardInputsWrapper;
}

Core::CoreType::Interface::IKeyboardInputs* Module::Inputs::GetKeyboardInputsWrapper() const
{
	return keyboardInputsWrapper;
}

Core::CoreType::Interface::IKeyboardInputs* Module::Inputs::Keyboard() const
{
	return GetKeyboardInputsWrapper();
}

bool Module::Inputs::Initialize()
{
	return true;
}

bool Module::Inputs::Start()
{
	return true;
}

bool Module::Inputs::Update()
{
	return true;
}

bool Module::Inputs::Destruct()
{
	return true;
}


