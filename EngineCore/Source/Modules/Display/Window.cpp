#include "Modules/Display/Window.h"
#include "Modules/Inputs/Input.h"

#include <windowsx.h>

Module::Inputs::WindowsKeyboard* Module::Display::Window::windowKeyboardInputsInstance = nullptr;
Module::Inputs::WindowsMouse* Module::Display::Window::windowMouseInputsInstance = nullptr;

Module::Display::Window::~Window()
{
	PostQuitMessage(0);
}

bool Module::Display::Window::Initialize()
{
	hInstance = engine->GetHInstance();
	fullscreen = GET_BOOL_PARAMETER("Display", "fullscreen");

	const int width_parameter = GET_INT_PARAMETER("Display", "width");
	const int height_parameter = GET_INT_PARAMETER("Display", "height");

	return PrepareWindow(width_parameter, height_parameter);
}

bool Module::Display::Window::Start()
{
	windowKeyboardInputsInstance = dynamic_cast<Inputs::WindowsKeyboard*>(Module<Inputs::Input>()->CreateKeyboardInputsWrapper(Inputs::KeyboardInputsApi::Windows));
	windowMouseInputsInstance = dynamic_cast<Inputs::WindowsMouse*>(Module<Inputs::Input>()->CreateMouseInputsWrapper(Inputs::MouseInputsApi::Windows));

	return MakeWindow(1);
}

bool Module::Display::Window::PrepareWindow(const int _width, const int _height)
{
	if (fullscreen)
	{
		HMONITOR__* const monitor = MonitorFromWindow(windowHandler, MONITOR_DEFAULTTONEAREST);
		MONITORINFO monitor_infos = { sizeof monitor_infos };
		GetMonitorInfo(monitor, &monitor_infos);

		width = monitor_infos.rcMonitor.right - monitor_infos.rcMonitor.left;
		height = monitor_infos.rcMonitor.bottom - monitor_infos.rcMonitor.top;
	}
	else
	{
		width = _width;
		height = _height;
	}

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = NULL;
	windowClass.cbWndExtra = NULL;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = HBRUSH(COLOR_WINDOW + 2);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = LPCTSTR(windowClassName);
	windowClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	if (!RegisterClassEx(&windowClass))
	{
		MessageBox(nullptr, L"Error registering class", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

bool Module::Display::Window::MakeWindow(const int _show_window)
{
	windowHandler = CreateWindowEx(NULL, windowClassName, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, nullptr);

	if (!windowHandler)
	{
		MessageBox(nullptr, L"Error creating window", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (fullscreen)
		SetWindowLong(windowHandler, GWL_STYLE, 0);

	ShowWindow(windowHandler, _show_window);
	UpdateWindow(windowHandler);

	return true;
}

LRESULT CALLBACK Module::Display::Window::WndProc(HWND__* _window_handle, const UINT _message, const WPARAM _window_parameter, const LPARAM _long_parameter)
{
	if (Engine::GetInstance()->IsRunning())
	{
		switch (_message)
		{
		case WM_KEYDOWN:
			if(windowKeyboardInputsInstance)
				windowKeyboardInputsInstance->KeyDown(static_cast<unsigned>(_window_parameter));
			return 0;
		case WM_KEYUP:
			if(windowKeyboardInputsInstance)
				windowKeyboardInputsInstance->KeyUp(static_cast<unsigned>(_window_parameter));
			return 0;

		case WM_LBUTTONDOWN:
			if (windowMouseInputsInstance)
				windowMouseInputsInstance->LeftMouseButtonDown();
			return 0;
		case WM_RBUTTONDOWN:
			if (windowMouseInputsInstance)
				windowMouseInputsInstance->RightMouseButtonDown();
			return 0;
		case WM_MBUTTONDOWN:
			if (windowMouseInputsInstance)
				windowMouseInputsInstance->MiddleMouseButtonDown();
			return 0;
		case WM_LBUTTONUP:
			if (windowMouseInputsInstance)
				windowMouseInputsInstance->LeftMouseButtonUp();
			return 0;
		case WM_RBUTTONUP:
			if (windowMouseInputsInstance)
				windowMouseInputsInstance->RightMouseButtonUp();
			return 0;
		case WM_MBUTTONUP:
			if (windowMouseInputsInstance)
				windowMouseInputsInstance->MiddleMouseButtonUp();
			return 0;

		case WM_MOUSEMOVE:
			if (windowMouseInputsInstance)
				windowMouseInputsInstance->SetMousePosition(GET_X_LPARAM(_long_parameter), GET_Y_LPARAM(_long_parameter));
			return 0;

		case WM_DESTROY:
			Engine::GetInstance()->Stop();
			return 0;



		default:
			return DefWindowProc(_window_handle, _message, _window_parameter, _long_parameter);
		}
	}

	return DefWindowProc(_window_handle, _message, _window_parameter, _long_parameter);
}

void Module::Display::Window::GetMessages()
{
	MSG message;
	ZeroMemory(&message, sizeof(MSG));

	if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
	{
		if (message.message == WM_QUIT)
			Engine::GetInstance()->Stop();

		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

bool Module::Display::Window::Update()
{
	GetMessages();

	return true;
}

bool Module::Display::Window::Destruct()
{
	if (windowHandler)
	{
		const bool result = DestroyWindow(windowHandler) != 0;
		windowHandler = nullptr;
		return result;
	}

	PostQuitMessage(0);

	return true;
}