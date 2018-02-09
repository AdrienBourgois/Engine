#pragma once

#include "Maths/Vec2.h"

namespace Core
{
	namespace Interface
	{
		class ENGINEDLL_API IMouseInputs
		{
		public:
			virtual ~IMouseInputs() = default;

			virtual void SetMousePosition(int _x, int _y) = 0;
			virtual Math::Vec2 GetMousePosition() const = 0;

			virtual void LeftMouseButtonDown() = 0;
			virtual void RightMouseButtonDown() = 0;
			virtual void MiddleMouseButtonDown() = 0;

			virtual void LeftMouseButtonUp() = 0;
			virtual void RightMouseButtonUp() = 0;
			virtual void MiddleMouseButtonUp() = 0;

			virtual bool IsLeftMouseButtonDown() const = 0;
			virtual bool IsRightMouseButtonDown() const = 0;
			virtual bool IsMiddleMouseButtonDown() const = 0;

		protected:
			bool isOnWindow = false;

			Math::Vec2 mousePosition = { 0, 0 };

			bool leftButtonDown = false;
			bool rightButtonDown = false;
			bool middleButtonDown = false;
		};
	}
}
