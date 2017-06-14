#include "WindowsKeyboard.h"

WindowsKeyboard::WindowsKeyboard()
{
	for (std::pair<Key, unsigned> pair : keyToWindowsMap)
		keyStates.insert_or_assign(static_cast<unsigned>(pair.first), false);
}

bool WindowsKeyboard::IsKeyDown(Key _key)
{
	unsigned key = keyToWindowsMap[_key];
	if(keyStates.find(key) != keyStates.end())
		return keyStates[key];

	return false;
}

void WindowsKeyboard::KeyUp(unsigned _key)
{
	if(keyStates.find(_key) != keyStates.end())
		keyStates[_key] = false;
}

void WindowsKeyboard::KeyDown(unsigned _key)
{
	if(keyStates.find(_key) != keyStates.end())
		keyStates[_key] = true;
}