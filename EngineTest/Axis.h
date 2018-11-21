#pragma once

#include "Scripts/GameObjectScript.h"

class Axis : public Scripts::Script
{
public:
	DECLARE_SCRIPT(S("Axis"), EObjectSubtype::SimpleScript);

	void Start() override
	{
		x.MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube, Color::Red);
		x.GetTransformReference()->scale = Math::Vec3(20.f, 0.1f, 0.1f);
		x.GetTransformReference()->position = Math::Vec3(10.f, 0.f, 0.f);

		y.MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube, Color::Green);
		y.GetTransformReference()->scale = Math::Vec3(0.1f, 20.f, 0.1f);
		y.GetTransformReference()->position = Math::Vec3(0.f, 10.f, 0.f);

		z.MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube, Color::Blue);
		z.GetTransformReference()->scale = Math::Vec3(0.1f, 0.1f, 20.f);
		z.GetTransformReference()->position = Math::Vec3(0.f, 0.f, 10.f);
	}

private:
	Object::GameObject x;
	Object::GameObject y;
	Object::GameObject z;
};
