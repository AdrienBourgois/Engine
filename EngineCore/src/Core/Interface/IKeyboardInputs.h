#pragma once

#include "Engine.h"

#include "Modules/Inputs/KeyList.h"

namespace Core
{
	namespace CoreType
	{
		namespace Interface
		{
			class ENGINEDLL_API IKeyboardInputs
			{
			public:
				virtual ~IKeyboardInputs() = default;

				virtual bool IsKeyDown(Key _key) = 0;

				virtual void KeyUp(unsigned _key) = 0;
				virtual void KeyDown(unsigned _key) = 0;
			};
		}
	}
}
