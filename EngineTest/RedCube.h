#pragma once

#include "Engine.h"
#include "Scripts/GameObjectScript.h"
#include "Core/CoreType/Container/Vector.h"

class RedCube : public Scripts::GameObjectScript
{
public:
	DECLARE_SCRIPT(S("RedCube"), EObjectSubtype::SimpleScript)

	Container::Vector<Object::GameObject*> objects;

	void Start() override
	{
		object.MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube);
		object.GetTransformReference()->rotation.y += 45.f;

		for (int x = 0; x < 10; ++x)
		{
			for (int z = 0; z < 10; ++z)
			{
				Object::GameObject* o = new Object::GameObject();
				o->MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube, Color(unsigned char(25 * x) , 0, 0, char(255)));
				o->GetTransformReference()->position = Math::Vec3(x * 5.f, 0.f, z * 5.f);
				o->GetTransformReference()->rotation = Math::Vec3(0.3f, 0.3f, 0.3f);
				objects += o;
			}
		}
	}

	void Update(const float _delta) override
	{
		if (Keyboard->IsKeyDown(Key::Escape))
			ENGINE->Stop();

		Transform transform = object.GetTransform();

		transform.scale = {0.3f, 0.3f, 0.3f};
		transform.rotation.x += _delta / 5.f;
		object.SetTransform(transform);

		for (auto it = objects.Begin(); it != objects.End(); ++it)
		{
			(*it)->GetTransformReference()->rotation.x += _delta/  5.f;
		}


	}

	void Destruct() override
	{
		for (auto it = objects.Begin(); it != objects.End(); ++it)
		{
			delete *it;
		}
	}
};
