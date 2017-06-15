#include "Input.h"
#include "WindowsKeyboard.h"

Module::Inputs::Input::~Input()
{
	delete keyboardInputsWrapper;
}

Core::Interface::IKeyboardInputs* Module::Inputs::Input::CreateKeyboardInputsWrapper(KeyboardInputsApi _api)
{
	if (_api == KeyboardInputsApi::Windows)
		keyboardInputsWrapper = new WindowsKeyboard;

	return keyboardInputsWrapper;
}

Core::Interface::IKeyboardInputs* Module::Inputs::Input::GetKeyboardInputsWrapper() const
{
	return keyboardInputsWrapper;
}

bool Module::Inputs::Input::Initialize()
{
	return true;
}

bool Module::Inputs::Input::Start()
{
	return true;
}

bool Module::Inputs::Input::Update()
{
	return true;
}

bool Module::Inputs::Input::Destruct()
{
	return true;
}


