#include "WindowsMouse.h"

void Module::Inputs::WindowsMouse::SetMousePosition(int _x, int _y)
{
	mousePosition.x = _x;
	mousePosition.y = _y;
}

Math::Vec2 Module::Inputs::WindowsMouse::GetMousePosition() const
{
	return mousePosition;
}

void Module::Inputs::WindowsMouse::LeftMouseButtonDown()
{
	leftButtonDown = true;
}

void Module::Inputs::WindowsMouse::RightMouseButtonDown()
{
	rightButtonDown = true;
}

void Module::Inputs::WindowsMouse::MiddleMouseButtonDown()
{
	middleButtonDown = true;
}

void Module::Inputs::WindowsMouse::LeftMouseButtonUp()
{
	leftButtonDown = false;
}

void Module::Inputs::WindowsMouse::RightMouseButtonUp()
{
	rightButtonDown = false;
}

void Module::Inputs::WindowsMouse::MiddleMouseButtonUp()
{
	middleButtonDown = false;
}

bool Module::Inputs::WindowsMouse::IsLeftMouseButtonDown() const
{
	return leftButtonDown;
}

bool Module::Inputs::WindowsMouse::IsRightMouseButtonDown() const
{
	return rightButtonDown;
}

bool Module::Inputs::WindowsMouse::IsMiddleMouseButtonDown() const
{
	return middleButtonDown;
}
