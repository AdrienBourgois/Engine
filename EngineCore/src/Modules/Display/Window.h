#pragma once

#include <Windows.h>

#include "Engine.h"

#include "Core/Interface/IModule.h"
#include "Modules/Inputs/WindowsKeyboard.h"

namespace Module
{
	namespace Display
	{
		class ENGINEDLL_API Window : public Core::Interface::IModule
		{
		public:
			Window() = default;
			~Window();

			DECLARE_MODULE(S("Window"))

			static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
			void GetMessages() const;

			bool isFullscreen() const { return fullscreen; }
			unsigned int getWidth() const { return width; }
			unsigned int getHeight() const { return height; }
			HWND* getHandle() { return &windowHandler; }

		private:
			bool PrepareWindow(int _width, int _height);
			bool MakeWindow(int _showWindow);

			HINSTANCE hInstance = nullptr;
			HWND windowHandler = nullptr;

			WNDCLASSEX windowClass;
			const wchar_t* windowClassName  = L"MainWindow";

			const wchar_t* windowTitle = L"Window Title";

			unsigned int width  = 1440;
			unsigned int height = 900;

			bool fullscreen = false;
			bool canReceiveMessage = true;

			static WindowsKeyboard* windowInputsInstance;
		};
	}
}

