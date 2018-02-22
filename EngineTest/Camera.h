#pragma once

#include "Engine.h"
#include "Scripts/Script.h"

class CameraScript : public Scripts::Script
{
public:
	DECLARE_SCRIPT(S("Camera"), EObjectSubtype::SimpleScript)

	void Start() override
	{
		Transform transform = Camera->GetTransform();
		transform.position.z = 4.f;
		transform.rotation = 0.f;
		Camera->SetTransform(transform);
	}

	void Update(const float _delta) override
	{
		Transform transform = Camera->GetTransform();
		if (Keyboard->IsKeyDown(Key::A))
			transform.rotation.y += 0.1f * _delta;
		if (Keyboard->IsKeyDown(Key::D))
			transform.rotation.y -= 0.1f * _delta;
		if (Keyboard->IsKeyDown(Key::W))
			transform.rotation.x += 0.1f * _delta;
		if (Keyboard->IsKeyDown(Key::S))
			transform.rotation.x -= 0.1f * _delta;

		if (Keyboard->IsKeyDown(Key::Left))
			transform.position.x -= 0.01f * _delta;
		if (Keyboard->IsKeyDown(Key::Right))
			transform.position.x += 0.01f * _delta;
		if (Keyboard->IsKeyDown(Key::Down))
			transform.position.z += 0.01f * _delta;
		if (Keyboard->IsKeyDown(Key::Up))
			transform.position.z -= 0.01f * _delta;
		Camera->SetTransform(transform);
	}
};
