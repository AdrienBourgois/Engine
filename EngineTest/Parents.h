#pragma once

#include "Scripts/Script.h"
#include "Objects/GameObject.h"

class Parents : public Scripts::Script
{
public:
	DECLARE_SCRIPT(S("Parents"), EObjectSubtype::SimpleScript)

	Object::GameObject* parent = nullptr;
	Object::GameObject* child = nullptr;

	void Start() override
	{
		parent = new Object::GameObject(S("Parent"));
		child = new Object::GameObject(S("Parent"));

		parent->MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube, Color::Pink);
		child->MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube, Color::Brown);

		child->SetParent(parent);

		child->GetTransformReference()->position.x += 6.f;
	}

	void Update(const float _delta) override
	{
		parent->GetTransformReference()->rotation.z += 0.3f * _delta;

		Transform transform = parent->GetTransform();

		if (Keyboard->IsKeyDown(Key::Up))
			transform.position.y += _delta * 0.01f;
		if (Keyboard->IsKeyDown(Key::Down))
			transform.position.y -= _delta * 0.01f;

		if (Keyboard->IsKeyDown(Key::Right))
			transform.position.x += _delta * 0.01f;
		if (Keyboard->IsKeyDown(Key::Left))
			transform.position.x -= _delta * 0.01f;

		transform.scale = {0.3f, 0.3f, 0.3f};
		parent->SetTransform(transform);
	}

	void Destruct() override
	{
		delete parent;
	}
};
