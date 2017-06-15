#pragma once

#include "Engine.h"
#include "Scripts/GameObjectScript.h"

class ScriptTest : public Scripts::GameObjectScript
{
public:
	DECLARE_SCRIPT(S("Script Test"), SimpleScript)

	void Start() override
	{
		MakeMesh(PrimitiveMesh::PrimitivesMeshType::Cube);
	}

	void Update(float _delta) override
	{
		if (Keyboard->IsKeyDown(Key::Escape))
			ENGINE->Stop();

		Transform transform = object.GetTransform();

		if (Keyboard->IsKeyDown(Key::Up))
			transform.position.y += _delta * 0.01f;
		if (Keyboard->IsKeyDown(Key::Down))
			transform.position.y -= _delta * 0.01f;

		if (Keyboard->IsKeyDown(Key::Right))
			transform.position.x += _delta * 0.01f;
		if (Keyboard->IsKeyDown(Key::Left))
			transform.position.x -= _delta * 0.01f;

		transform.scale = { 0.3f, 0.3f, 0.3f };
		transform.rotation.x += _delta / 5.f;
		object.SetTransform(transform);
	}
};
