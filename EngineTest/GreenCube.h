#pragma once

#include "Scripts/GameObjectScript.h"

class GreenCube : public Scripts::GameObjectScript
{
public:
	DECLARE_SCRIPT(S("GreenCube"), EObjectSubtype::GameScript)

	void Start() override
	{
		object.MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube, Color::Green);
		object.GetTransformReference()->position += 0.5f;
	}

	void Update(const float _delta) override
	{
		Transform transform = object.GetTransform();

		if (Keyboard->IsKeyDown(Key::Up))
			transform.position.y -= _delta * 0.01f;
		if (Keyboard->IsKeyDown(Key::Down))
			transform.position.y += _delta * 0.01f;

		if (Keyboard->IsKeyDown(Key::Right))
			transform.position.x -= _delta * 0.01f;
		if (Keyboard->IsKeyDown(Key::Left))
			transform.position.x += _delta * 0.01f;

		transform.scale = {0.3f, 0.3f, 0.3f};
		transform.rotation.x += _delta / 5.f;
		object.SetTransform(transform);
	}
};
