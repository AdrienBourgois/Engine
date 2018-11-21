#pragma once

#include "Engine.h"

#include "Modules/Inputs/KeyList.h"

namespace Core
{
	namespace Interface
	{
		/**
		* \brief Interface for keyboards inputs wrappers
		*/
		class ENGINEDLL_API IKeyboardInputs
		{
		public:
			/**
			* \brief Virtual default destructor
			*/
			virtual ~IKeyboardInputs() = default;

			/**
			* \brief Test if a key is pressed
			* \param _key Key to test
			* \return Is key pressed
			*/
			virtual bool IsKeyDown(EKey _key) = 0;

			/**
			* \brief Notify that a key has been pressed
			* \param _key Id of key
			*/
			virtual void KeyUp(unsigned _key) = 0;
			/**
			* \brief Notify that a key has been released
			* \param _key Id of key
			*/
			virtual void KeyDown(unsigned _key) = 0;
		};
	}
}
