#include "Input.h"
#include "WindowsKeyboard.h"
#include "WindowsMouse.h"

Module::Inputs::Input::~Input()
{
	delete keyboardInputsWrapper;
	keyboardInputsWrapper = nullptr;
	delete mouseInputsWrapper;
	mouseInputsWrapper = nullptr;
}

Core::Interface::IKeyboardInputs* Module::Inputs::Input::CreateKeyboardInputsWrapper(KeyboardInputsApi _api)
{
	if (_api == KeyboardInputsApi::Windows)
		keyboardInputsWrapper = new WindowsKeyboard;

	return keyboardInputsWrapper;
}

Core::Interface::IMouseInputs* Module::Inputs::Input::CreateMouseInputsWrapper(MouseInputsApi _api)
{
	if (_api == MouseInputsApi::Windows)
		mouseInputsWrapper = new WindowsMouse;

	return mouseInputsWrapper;
}

Core::Interface::IKeyboardInputs* Module::Inputs::Input::GetKeyboardInputsWrapper() const
{
	return keyboardInputsWrapper;
}

Core::Interface::IMouseInputs* Module::Inputs::Input::GetMouseInputsWrapper() const
{
	return mouseInputsWrapper;
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


