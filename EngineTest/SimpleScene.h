#pragma once

#include "Scripts/GameObjectScript.h"

class SimpleScene : public Scripts::Script
{
public:
	DECLARE_SCRIPT(S("SimpleScene"), EObjectSubtype::SimpleScript);

	void Start() override
	{
		plane.MakeMesh(PrimitiveMesh::PrimitivesMeshType::Plane, Color::Grey);
		plane.GetTransformReference()->scale = Math::Vec3(5.f);

		cube.MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube);
		cube.GetTransformReference()->position = Math::Vec3(0.f, 0.5f, 0.f);
	}

private:
	Object::GameObject plane;
	Object::GameObject cube;
};
