#pragma once

#include "Engine.h"
#include "Scripts/GameObjectScript.h"
#include "Core/CoreType/Container/Vector.h"

class RedCube : public Scripts::GameObjectScript
{
public:
	DECLARE_SCRIPT(S("RedCube"), EObjectSubtype::SimpleScript)

	Container::Vector<Object::GameObject*> Objects;

	void Start() override
	{
		object.MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube);
		object.GetTransformReference()->rotation.y += 45.f;

		for (int x = 0; x < 2; ++x)
		{
			for (int z = 0; z < 2; ++z)
			{
				Object::GameObject* o = new Object::GameObject();
				o->MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube);
				o->GetTransformReference()->position = Math::Vec3(x * 5.f, 0.f, z * 5.f);
				o->GetTransformReference()->rotation = Math::Vec3(0.3f, 0.3f, 0.3f);
				Objects += o;
			}
		}
	}

	void Update(const float _delta) override
	{
		Transform transform = object.GetTransform();

		transform.scale = {0.3f, 0.3f, 0.3f};
		transform.rotation.x += _delta / 5.f;
		object.SetTransform(transform);

		for (auto it = Objects.Begin(); it != Objects.End(); ++it)
		{
			(*it)->GetTransformReference()->rotation.x += _delta/  5.f;
		}


	}

	void Destruct() override
	{
		for (auto it = Objects.Begin(); it != Objects.End(); ++it)
		{
			delete *it;
		}
	}
};
