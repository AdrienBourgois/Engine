#pragma once

#include <Windows.h>

#include "Engine.h"

#include "IModule.h"

namespace Display
{
	class ENGINEDLL_API Window : public IModule
	{
	public:
		Window();
		~Window();

		DECLARE_MODULE("Window")

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void GetMessages() const;

		bool isFullscreen() const { return fullscreen; }
		int getWidth() const { return width; }
		int getHeight() const { return height; }
		HWND* getHandle() { return &windowHandler; }

	private:
		bool PrepareWindow(int _width, int _height);
		bool MakeWindow(int _showWindow);

		HINSTANCE hInstance = nullptr;
		HWND windowHandler = nullptr;

		WNDCLASSEX windowClass;
		const wchar_t* windowClassName  = L"MainWindow";

		const wchar_t* windowTitle = L"Window Title";

		int width  = 1440;
		int height = 900;

		bool fullscreen = false;
		bool canReceiveMessage = true;
	};
}

