#pragma once

#include "Maths/Mat4.h"

namespace Core
{
	namespace CoreType
	{
		/**
		 * \brief Handle transformation for an object
		 */
		class ENGINEDLL_API Transform
		{
		public:
			/**
			 * \brief Constructor
			 * \param _parent Transform parent
			 */
			explicit Transform(Transform* _parent = nullptr);
			/**
			 * \brief Default destructor
			 */
			~Transform() = default;

			/**
			 * \brief Position transformation
			 */
			Math::Vec3 position = Math::Vec3(0.f);
			/**
			 * \brief Rotation transformation
			 */
			Math::Vec3 rotation = Math::Vec3(0.f);
			/**
			 * \brief Scale transformation
			 */
			Math::Vec3 scale = Math::Vec3(1.f);

			/**
			 * \brief Get a local matrix for this transformation
			 * \return Local matrix
			 */
			const Math::Mat4 GetLocalMatrix() const;
			/**
			 * \brief Get the world matrix for this transformation
			 * \return World matrix
			 */
			const Math::Mat4 GetWorldMatrix() const;

			/**
			 * \brief Set a new parent for this transform
			 * \param _new_parent New parent
			 */
			void SetParent(Transform* _new_parent);

		private:
			/**
			 * \brief Cache for local matrix
			 */
			Math::Mat4 localMatrix = Math::Mat4::Identity;
			/**
			 * \brief Pointer to the transform parent
			 */
			Transform* parent = nullptr;
		};
	}
}

