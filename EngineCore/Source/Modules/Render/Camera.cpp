#include "Camera.h"
#include "Modules/Display/Window.h"

Module::Render::Camera::Camera()
{
	const Display::Window* window = Engine::GetInstance()->GetModule<Display::Window>();
	width = static_cast<FLOAT>(window->GetWidth());
	height = static_cast<FLOAT>(window->GetHeight());
}

void Module::Render::Camera::SetAsActiveCamera()
{
	isActiveCamera = true;
}

Core::CoreType::Transform Module::Render::Camera::GetTransform() const
{
	return transform;
}

Math::Mat4 Module::Render::Camera::GetProjectionMatrix() const
{
	return Math::Mat4::PerspectiveMatrix(fov, width / height, nearRender, farRender);
}

Math::Mat4 Module::Render::Camera::GetViewMatrix() const
{
	return transform.GetWorldMatrix();
}

float Module::Render::Camera::GetFov() const
{
	return fov;
}

float Module::Render::Camera::GetNear() const
{
	return nearRender;
}

float Module::Render::Camera::GetFar() const
{
	return farRender;
}

void Module::Render::Camera::SetFov(const float _fov)
{
	fov = _fov;
}

void Module::Render::Camera::SetNear(const float _near)
{
	nearRender = _near;
}

void Module::Render::Camera::SetFar(const float _far)
{
	farRender = _far;
}

void Module::Render::Camera::SetTransform(const Core::CoreType::Transform _transform)
{
	transform = _transform;
}

