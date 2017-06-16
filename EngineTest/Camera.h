#pragma once

#include "Engine.h"
#include "Scripts/Script.h"

class CameraScript : public Scripts::Script
{
public:
	DECLARE_SCRIPT(S("Camera"), EObjectSubtype::SimpleScript)

	void Start() override
	{

	}

	void Update(float _delta) override
	{
		if (Keyboard->IsKeyDown(Key::A))
		{
			Transform transform = Camera->GetTransform();
			transform.rotation.y += 0.1f * _delta;
			Camera->SetTransform(transform);
		}
	}
};
