#include "Core/CoreType/Transform.h"

Core::CoreType::Transform::Transform(Transform* _parent): parent(_parent)
{}

Core::CoreType::Transform::Transform(const Math::Vec3 _position, const Math::Vec3 _rotation, const Math::Vec3 _scale): position(_position), rotation(_rotation), scale(_scale)
{}

Math::Mat4 Core::CoreType::Transform::GetLocalMatrix() const
{
	return Math::Mat4::Scale(scale) * Math::Mat4::Rotate(rotation) * Math::Mat4::Translate(position);
}

Math::Mat4 Core::CoreType::Transform::GetWorldMatrix() const
{
	if(parent)
		return GetLocalMatrix() * parent->GetWorldMatrix();

	return GetLocalMatrix();
}

void Core::CoreType::Transform::SetParent(Transform* _new_parent)
{
	parent = _new_parent;
}
