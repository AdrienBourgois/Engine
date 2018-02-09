#pragma once

#include "Core/Interface/IMouseInputs.h"

namespace Module
{
	namespace Inputs
	{
		class WindowsMouse : public Core::Interface::IMouseInputs
		{
		public:
			WindowsMouse() = default;
			~WindowsMouse() = default;

			void SetMousePosition(int _x, int _y) override;
			Math::Vec2 GetMousePosition() const override;

			void LeftMouseButtonDown() override;
			void RightMouseButtonDown() override;
			void MiddleMouseButtonDown() override;

			void LeftMouseButtonUp() override;
			void RightMouseButtonUp() override;
			void MiddleMouseButtonUp() override;

			bool IsLeftMouseButtonDown() const override;
			bool IsRightMouseButtonDown() const override;
			bool IsMiddleMouseButtonDown() const override;
		};
	}
}

