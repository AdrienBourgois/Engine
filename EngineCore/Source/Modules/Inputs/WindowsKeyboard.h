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
			bool IsKeyDown(EKey _key) override;
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
			std::unordered_map<EKey, unsigned> keyToWindowsMap
			{
				{EKey::A, 'A'},
				{EKey::B, 'B'},
				{EKey::C, 'C'},
				{EKey::D, 'D'},
				{EKey::E, 'E'},
				{EKey::F, 'F'},
				{EKey::G, 'G'},
				{EKey::H, 'H'},
				{EKey::I, 'I'},
				{EKey::J, 'J'},
				{EKey::K, 'K'},
				{EKey::L, 'L'},
				{EKey::M, 'M'},
				{EKey::N, 'N'},
				{EKey::O, 'O'},
				{EKey::P, 'P'},
				{EKey::Q, 'Q'},
				{EKey::R, 'R'},
				{EKey::S, 'S'},
				{EKey::T, 'T'},
				{EKey::U, 'U'},
				{EKey::V, 'V'},
				{EKey::W, 'W'},
				{EKey::X, 'X'},
				{EKey::Y, 'Y'},
				{EKey::Z, 'Z'},
				{EKey::Num0, '0'},
				{EKey::Num1, '1'},
				{EKey::Num2, '2'},
				{EKey::Num3, '3'},
				{EKey::Num4, '4'},
				{EKey::Num5, '5'},
				{EKey::Num6, '6'},
				{EKey::Num7, '7'},
				{EKey::Num8, '8'},
				{EKey::Num9, '9'},
				{EKey::Escape, VK_ESCAPE},
				{EKey::LControl, VK_LCONTROL},
				{EKey::LShift, VK_LSHIFT},
				{EKey::LAlt, VK_LMENU},
				{EKey::RControl, VK_RCONTROL},
				{EKey::RShift, VK_RSHIFT},
				{EKey::RAlt, VK_RMENU},
				{EKey::Menu, VK_MENU},
				{EKey::LBracket, VK_OEM_4},
				{EKey::RBracket, VK_OEM_6},
				{EKey::SemiColon, VK_OEM_1},
				{EKey::Comma, VK_OEM_COMMA},
				{EKey::Period, VK_OEM_PERIOD},
				{EKey::Quote, VK_OEM_7},
				{EKey::Slash, VK_OEM_2},
				{EKey::BackSlash, VK_OEM_5},
				{EKey::Tilde, VK_OEM_3},
				{EKey::Space, VK_SPACE},
				{EKey::Return, VK_RETURN},
				{EKey::BackSpace, VK_BACK},
				{EKey::Tab, VK_TAB},
				{EKey::PageUp, VK_PRIOR},
				{EKey::PageDown, VK_NEXT},
				{EKey::End, VK_END},
				{EKey::Home, VK_HOME},
				{EKey::Insert, VK_INSERT},
				{EKey::Delete, VK_DELETE},
				{EKey::Add, VK_ADD},
				{EKey::Subtract, VK_SUBTRACT},
				{EKey::Multiply, VK_MULTIPLY},
				{EKey::Divide, VK_DIVIDE},
				{EKey::Left, VK_LEFT},
				{EKey::Right, VK_RIGHT},
				{EKey::Up, VK_UP},
				{EKey::Down, VK_DOWN},
				{EKey::Numpad0, VK_NUMPAD0},
				{EKey::Numpad1, VK_NUMPAD1},
				{EKey::Numpad2, VK_NUMPAD2},
				{EKey::Numpad3, VK_NUMPAD3},
				{EKey::Numpad4, VK_NUMPAD4},
				{EKey::Numpad5, VK_NUMPAD5},
				{EKey::Numpad6, VK_NUMPAD6},
				{EKey::Numpad7, VK_NUMPAD7},
				{EKey::Numpad8, VK_NUMPAD8},
				{EKey::Numpad9, VK_NUMPAD9},
				{EKey::F1, VK_F1},
				{EKey::F2, VK_F2},
				{EKey::F3, VK_F3},
				{EKey::F4, VK_F4},
				{EKey::F5, VK_F5},
				{EKey::F6, VK_F6},
				{EKey::F7, VK_F7},
				{EKey::F8, VK_F8},
				{EKey::F9, VK_F9},
				{EKey::F10, VK_F10},
				{EKey::F11, VK_F11},
				{EKey::F12, VK_F12},
				{EKey::F13, VK_F13},
				{EKey::F14, VK_F14},
				{EKey::F15, VK_F15},
				{EKey::Pause, VK_PAUSE},
			};
		};
	}
}
