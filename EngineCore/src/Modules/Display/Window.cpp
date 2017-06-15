#include "Modules/Display/Window.h"
#include "Modules/Inputs/Input.h"

Module::Inputs::WindowsKeyboard* Module::Display::Window::windowInputsInstance = nullptr;

Module::Display::Window::~Window()
{
	PostQuitMessage(0);
}

bool Module::Display::Window::Initialize()
{
	hInstance = ENGINE->GetHInstance();
	fullscreen = GET_BOOL_PARAMETER("Display", "fullscreen");

	int width_parameter = GET_INT_PARAMETER("Display", "width");
	int height_parameter = GET_INT_PARAMETER("Display", "height");

	return PrepareWindow(width_parameter, height_parameter);
}

bool Module::Display::Window::Start()
{
	windowInputsInstance = static_cast<Inputs::WindowsKeyboard*>(MODULE(Module::Inputs::Input)->CreateKeyboardInputsWrapper(Inputs::KeyboardInputsApi::Windows));

	return MakeWindow(1);
}

bool Module::Display::Window::PrepareWindow(int _width, int _height)
{
	if (fullscreen)
	{
		HMONITOR hmon = MonitorFromWindow(windowHandler, MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi = { sizeof mi };
		GetMonitorInfo(hmon, &mi);

		width = mi.rcMonitor.right - mi.rcMonitor.left;
		height = mi.rcMonitor.bottom - mi.rcMonitor.top;
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

bool Module::Display::Window::MakeWindow(int _showWindow)
{
	windowHandler = CreateWindowEx(NULL, windowClassName, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, nullptr);

	if (!windowHandler)
	{
		MessageBox(nullptr, L"Error creating window", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (fullscreen)
		SetWindowLong(windowHandler, GWL_STYLE, 0);

	ShowWindow(windowHandler, _showWindow);
	UpdateWindow(windowHandler);

	return true;
}

LRESULT CALLBACK Module::Display::Window::WndProc(HWND _windowHandle, UINT _message, WPARAM _windowParameter, LPARAM _longParameter)
{
	if (ENGINE->GetState() == Engine::EEngineStates::Running)
	{
		switch (_message)
		{
		case WM_KEYDOWN:
			if(windowInputsInstance)
				windowInputsInstance->KeyDown(static_cast<unsigned>(_windowParameter));
			return 0;
		case WM_KEYUP:
			if(windowInputsInstance)
				windowInputsInstance->KeyUp(static_cast<unsigned>(_windowParameter));
			return 0;

		case WM_DESTROY:
			ENGINE->Stop();
			return 0;

		default:
			return DefWindowProc(_windowHandle, _message, _windowParameter, _longParameter);
		}
	}

	return DefWindowProc(_windowHandle, _message, _windowParameter, _longParameter);
}

void Module::Display::Window::GetMessages() const
{
	MSG _message;
	ZeroMemory(&_message, sizeof(MSG));

	if (PeekMessage(&_message, nullptr, 0, 0, PM_REMOVE))
	{
		if (_message.message == WM_QUIT)
			ENGINE->Stop();

		TranslateMessage(&_message);
		DispatchMessage(&_message);
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
		bool result = DestroyWindow(windowHandler) != 0;
		windowHandler = nullptr;
		return result;
	}

	PostQuitMessage(0);

	return true;
}