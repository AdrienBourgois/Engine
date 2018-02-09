#include "Core/CoreType/Transform.h"

Core::CoreType::Transform::Transform(Transform* _parent): parent(_parent)
{}

Core::CoreType::Transform::Transform(Math::Vec3 _position, Math::Vec3 _rotation, Math::Vec3 _scale): position(_position), rotation(_rotation), scale(_scale)
{}

const Math::Mat4 Core::CoreType::Transform::GetLocalMatrix() const
{
	return Math::Mat4::Scale(scale) * Math::Mat4::Rotate(rotation) * Math::Mat4::Translate(position);
}

const Math::Mat4 Core::CoreType::Transform::GetWorldMatrix() const
{
	if(parent)
		return GetLocalMatrix() * parent->GetWorldMatrix();

	return GetLocalMatrix();
}

void Core::CoreType::Transform::SetParent(Transform* _new_parent)
{
	parent = _new_parent;
}
