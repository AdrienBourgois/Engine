#pragma once

#include "Macros.h"
#include "Core/CoreType/Transform.h"

namespace Module
{
	namespace Render
	{
		/**
		 * \brief Camera object used to render
		 */
		class ENGINEDLL_API Camera
		{
		public:
			/**
			 * \brief Constructor
			 */
			Camera();
			/**
			 * \brief Default destructor
			 */
			~Camera() = default;

			/**
			 * \brief Set camera as active camera
			 */
			void SetAsActiveCamera();

			/**
			 * \brief Return transform of this camera
			 * \return Camera transform
			 */
			Core::CoreType::Transform GetTransform() const;
			/**
			 * \brief Return projection matrix of this camera
			 * \return Camera projection matrix
			 */
			Math::Mat4 GetProjectionMatrix() const;
			/**
			 * \brief Return view matrix of this camera
			 * \return Camera view matrix
			 */
			Math::Mat4 GetViewMatrix() const;

			/**
			 * \brief Return field of view of this camera
			 * \return Camera Fov
			 */
			float GetFov() const;
			/**
			 * \brief Return nearest distance of render from this camera
			 * \return Camera near
			 */
			float GetNear() const;
			/**
			 * \brief Return farest distance of render from this camera
			 * \return Camera far
			 */
			float GetFar() const;

			/**
			 * \brief Set a new transform for this camera
			 * \param _transform New transform
			 */
			void SetTransform(Core::CoreType::Transform _transform);

			/**
			 * \brief Set a new fov for this camera
			 * \param _fov New fov
			 */
			void SetFov(float _fov);
			/**
			 * \brief Set a new near for this camera
			 * \param _near New near
			 */
			void SetNear(float _near);
			/**
			 * \brief Set a new far for this camera
			 * \param _far New far
			 */
			void SetFar(float _far);

		private:
			/**
			 * \brief Is this camera the current active camera
			 */
			bool isActiveCamera = false;

			/**
			 * \brief Width of this camera
			 */
			float width = 0;
			/**
			 * \brief Height of this camera
			 */
			float height = 0;
			/**
			 * \brief FOV of this camera
			 */
			float fov = 45.f;
			/**
			 * \brief Near of this camera
			 */
			float nearRender = 0.1f;
			/**
			 * \brief Near of this camera
			 */
			float farRender = 1000.f;

			/**
			 * \brief Camera transform
			 */
			Core::CoreType::Transform transform;
			/**
			 * \brief Camera projection matrix
			 */
			Math::Mat4 projectionMatrix;
		};
	}
}

