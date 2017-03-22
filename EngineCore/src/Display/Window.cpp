#include "Window.h"

Display::Window::Window()
{
}

Display::Window::~Window()
{
	PostQuitMessage(0);
}

bool Display::Window::Initialize()
{
	hInstance = ENGINE->GetHInstance();
	fullscreen = GET_BOOL_PARAMETER("Display", "fullscreen");

	int p_width = GET_INT_PARAMETER("Display", "width");
	int p_height = GET_INT_PARAMETER("Display", "height");

	return PrepareWindow(p_width, p_height);
}

bool Display::Window::Start()
{
	return MakeWindow(1);
}

bool Display::Window::PrepareWindow(int _width, int _height)
{
	if (fullscreen)
	{
		HMONITOR hmon = MonitorFromWindow(windowHandler, MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi = { sizeof(mi) };
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

bool Display::Window::MakeWindow(int _showWindow)
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

LRESULT CALLBACK Display::Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ENGINE->GetState() == Running)
	{
		switch (msg)
		{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
				if (MessageBox(nullptr, L"Are you sure you want to exit?", L"Really?", MB_YESNO | MB_ICONHAND) == IDYES)
					ENGINE->Stop();
			return 0;

		case WM_DESTROY:
			ENGINE->Stop();
			return 0;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Display::Window::GetMessages() const
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			ENGINE->Stop();

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

bool Display::Window::Update()
{
	GetMessages();

	return true;
}

bool Display::Window::Destruct()
{
	if (windowHandler)
	{
		bool result = DestroyWindow(windowHandler)!=0;
		windowHandler = nullptr;
		return result;
	}

	PostQuitMessage(0);

	return true;
}