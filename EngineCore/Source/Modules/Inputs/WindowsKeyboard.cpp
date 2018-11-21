#include "WindowsKeyboard.h"

Module::Inputs::WindowsKeyboard::WindowsKeyboard()
{
	for (std::pair<EKey, unsigned> pair : keyToWindowsMap)
		keyStates.insert_or_assign(static_cast<unsigned>(pair.first), false);
}

bool Module::Inputs::WindowsKeyboard::IsKeyDown(const EKey _key)
{
	const unsigned key = keyToWindowsMap[_key];
	if(keyStates.find(key) != keyStates.end())
		return keyStates[key];

	return false;
}

void Module::Inputs::WindowsKeyboard::KeyUp(const unsigned _key)
{
	if(keyStates.find(_key) != keyStates.end())
		keyStates[_key] = false;
}

void Module::Inputs::WindowsKeyboard::KeyDown(const unsigned _key)
{
	if(keyStates.find(_key) != keyStates.end())
		keyStates[_key] = true;
}