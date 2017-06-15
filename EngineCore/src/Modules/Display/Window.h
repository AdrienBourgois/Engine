#pragma once

#include <Windows.h>

#include "Engine.h"

#include "Core/Interface/IModule.h"
#include "Modules/Inputs/WindowsKeyboard.h"

namespace Module
{
	/**
	 * \brief Display modules : Window
	 */
	namespace Display
	{
		/**
		 * \brief Manage window and process messages from system
		 */
		class ENGINEDLL_API Window : public Core::Interface::IModule
		{
		public:
			DECLARE_MODULE(S("Window"))

			/**
			 * \brief Default constructor
			 */
			Window() = default;
			/**
			 * \brief Destructor
			 */
			~Window();

			/**
			 * \brief Callback function for system messages
			 * \param _windowHandle Handle to the window
			 * \param _message Message
			 * \param _windowParameter Message Parameter
			 * \param _longParameter Message Parameter
			 * \return Is message processed
			 */
			static LRESULT CALLBACK WndProc(HWND _windowHandle, UINT _message, WPARAM _windowParameter, LPARAM _longParameter);
			/**
			 * \brief Get and process messages from system
			 */
			void GetMessages() const;

			/**
			 * \brief Is window in fullscreen
			 * \return Is window in fullscreen
			 */
			bool isFullscreen() const { return fullscreen; }
			/**
			 * \brief Return width of the window
			 * \return Width of window
			 */
			unsigned int getWidth() const { return width; }
			/**
			 * \brief Return heigt of the window
			 * \return Width of window
			 */
			unsigned int getHeight() const { return height; }
			/**
			 * \brief Return the handle of the window
			 * \return Handle of window
			 */
			HWND* getHandle() { return &windowHandler; }

		private:
			/**
			 * \brief Create a window class
			 * \param _width Width of the window
			 * \param _height Height of the window
			 * \return Is window prepared
			 */
			bool PrepareWindow(int _width, int _height);
			/**
			 * \brief Create and display window
			 * \param _showWindow Must the window be show
			 * \return Is window created
			 */
			bool MakeWindow(int _showWindow);

			/**
			 * \brief Handle the instance
			 */
			HINSTANCE hInstance = nullptr;
			/**
			 * \brief Window handler
			 */
			HWND windowHandler = nullptr;

			/**
			 * \brief Class of window
			 */
			WNDCLASSEX windowClass;
			/**
			 * \brief Name of the window class
			 */
			const wchar_t* windowClassName  = L"MainWindow";

			/**
			 * \brief Title of the window
			 */
			const wchar_t* windowTitle = L"Window Title";

			/**
			 * \brief Store width of window
			 */
			unsigned int width  = 1440;
			/**
			 * \brief Store height of window
			 */
			unsigned int height = 900;

			/**
			 * \brief Store fulscreen state of window
			 */
			bool fullscreen = false;
			/**
			 * \brief Is window ready to get messages from system
			 */
			bool canReceiveMessage = true;

			/**
			 * \brief Pointer to the keyboard input wrapper to send messages
			 */
			static Inputs::WindowsKeyboard* windowInputsInstance;
		};
	}
}

