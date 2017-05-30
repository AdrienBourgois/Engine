#pragma once

#include "Maths/Mat4.h"

namespace Core
{
	namespace CoreType
	{
		class ENGINEDLL_API Transform
		{
		public:
			explicit Transform(Transform* _parent = nullptr);
			~Transform() = default;

			Math::Vec3 position = Math::Vec3(0.f);
			Math::Vec3 rotation = Math::Vec3(0.f);
			Math::Vec3 scale = Math::Vec3(1.f);

			const Math::Mat4 GetLocalMatrix() const;
			const Math::Mat4 GetWorldMatrix() const;

		private:
			Math::Mat4 localMatrix = Math::Mat4::Identity;
			Transform* parent = nullptr;
		};
	}
}

