#pragma once

#include <Windows.h>
#include <unordered_map>

#include "KeyList.h"
#include "Core/Interface/IKeyboardInputs.h"

namespace Module
{
	namespace Inputs
	{
		/**
		 * \brief Handle states of keys for Windows system
		 */
		class WindowsKeyboard : public Core::Interface::IKeyboardInputs
		{
		public:
			/**
			 * \brief Constructor
			 */
			WindowsKeyboard();
			/**
			 * \brief Default destructor
			 */
			~WindowsKeyboard() = default;

			/**
			 * \brief Test if a key is pressed
			 * \param _key Key to test
			 * \return Is key pressed
			 */
			bool IsKeyDown(Key _key) override;
			/**
			* \brief Notify that a key has been pressed
			* \param _key Id of key
			*/
			void KeyUp(unsigned _key) override;
			/**
			* \brief Notify that a key has been released
			* \param _key Id of key
			*/
			void KeyDown(unsigned _key) override;

			/**
			 * \brief Store states of keys
			 */
			std::unordered_map<unsigned, bool> keyStates;

		private:
			/**
			 * \brief Used for conversion between system virtual key and keys from engine
			 */
			std::unordered_map<Key, unsigned> keyToWindowsMap
			{
				{Key::A, 'A'},
				{Key::B, 'B'},
				{Key::C, 'C'},
				{Key::D, 'D'},
				{Key::E, 'E'},
				{Key::F, 'F'},
				{Key::G, 'G'},
				{Key::H, 'H'},
				{Key::I, 'I'},
				{Key::J, 'J'},
				{Key::K, 'K'},
				{Key::L, 'L'},
				{Key::M, 'M'},
				{Key::N, 'N'},
				{Key::O, 'O'},
				{Key::P, 'P'},
				{Key::Q, 'Q'},
				{Key::R, 'R'},
				{Key::S, 'S'},
				{Key::T, 'T'},
				{Key::U, 'U'},
				{Key::V, 'V'},
				{Key::W, 'W'},
				{Key::X, 'X'},
				{Key::Y, 'Y'},
				{Key::Z, 'Z'},
				{Key::Num0, '0'},
				{Key::Num1, '1'},
				{Key::Num2, '2'},
				{Key::Num3, '3'},
				{Key::Num4, '4'},
				{Key::Num5, '5'},
				{Key::Num6, '6'},
				{Key::Num7, '7'},
				{Key::Num8, '8'},
				{Key::Num9, '9'},
				{Key::Escape, VK_ESCAPE},
				{Key::LControl, VK_LCONTROL},
				{Key::LShift, VK_LSHIFT},
				{Key::LAlt, VK_LMENU},
				{Key::RControl, VK_RCONTROL},
				{Key::RShift, VK_RSHIFT},
				{Key::RAlt, VK_RMENU},
				{Key::Menu, VK_MENU},
				{Key::LBracket, VK_OEM_4},
				{Key::RBracket, VK_OEM_6},
				{Key::SemiColon, VK_OEM_1},
				{Key::Comma, VK_OEM_COMMA},
				{Key::Period, VK_OEM_PERIOD},
				{Key::Quote, VK_OEM_7},
				{Key::Slash, VK_OEM_2},
				{Key::BackSlash, VK_OEM_5},
				{Key::Tilde, VK_OEM_3},
				{Key::Space, VK_SPACE},
				{Key::Return, VK_RETURN},
				{Key::BackSpace, VK_BACK},
				{Key::Tab, VK_TAB},
				{Key::PageUp, VK_PRIOR},
				{Key::PageDown, VK_NEXT},
				{Key::End, VK_END},
				{Key::Home, VK_HOME},
				{Key::Insert, VK_INSERT},
				{Key::Delete, VK_DELETE},
				{Key::Add, VK_ADD},
				{Key::Subtract, VK_SUBTRACT},
				{Key::Multiply, VK_MULTIPLY},
				{Key::Divide, VK_DIVIDE},
				{Key::Left, VK_LEFT},
				{Key::Right, VK_RIGHT},
				{Key::Up, VK_UP},
				{Key::Down, VK_DOWN},
				{Key::Numpad0, VK_NUMPAD0},
				{Key::Numpad1, VK_NUMPAD1},
				{Key::Numpad2, VK_NUMPAD2},
				{Key::Numpad3, VK_NUMPAD3},
				{Key::Numpad4, VK_NUMPAD4},
				{Key::Numpad5, VK_NUMPAD5},
				{Key::Numpad6, VK_NUMPAD6},
				{Key::Numpad7, VK_NUMPAD7},
				{Key::Numpad8, VK_NUMPAD8},
				{Key::Numpad9, VK_NUMPAD9},
				{Key::F1, VK_F1},
				{Key::F2, VK_F2},
				{Key::F3, VK_F3},
				{Key::F4, VK_F4},
				{Key::F5, VK_F5},
				{Key::F6, VK_F6},
				{Key::F7, VK_F7},
				{Key::F8, VK_F8},
				{Key::F9, VK_F9},
				{Key::F10, VK_F10},
				{Key::F11, VK_F11},
				{Key::F12, VK_F12},
				{Key::F13, VK_F13},
				{Key::F14, VK_F14},
				{Key::F15, VK_F15},
				{Key::Pause, VK_PAUSE},
			};
		};
	}
}
