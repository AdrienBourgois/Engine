#pragma once

#include "Engine.h"
#include "Scripts/Script.h"
#include <iostream>

class CameraScript : public Scripts::Script
{
public:
	DECLARE_SCRIPT(S("Camera"), EObjectSubtype::SimpleScript)

	void Start() override
	{
		Module::Render::Camera* camera = GetRenderInterface()->GetActiveCamera();
		Transform transform = camera->GetTransform();
		transform.position = Math::Vec3(5.f);
		transform.rotation.x = -45.f;
		transform.rotation.y = -45.f;
		camera->SetTransform(transform);
	}

	void Update(const float _delta) override
	{
		Module::Render::Camera* camera = GetRenderInterface()->GetActiveCamera();
		Interface::IKeyboardInputs* keyboard = GetInputs()->GetKeyboardInputsWrapper();

		if (keyboard->IsKeyDown(EKey::Escape))
			Engine::GetInstance()->Stop();

		Transform transform = camera->GetTransform();

		if (keyboard->IsKeyDown(EKey::A))
			transform.rotation.y += 0.1f * _delta;
		if (keyboard->IsKeyDown(EKey::D))
			transform.rotation.y -= 0.1f * _delta;
		if (keyboard->IsKeyDown(EKey::W))
			transform.rotation.x += 0.1f * _delta;
		if (keyboard->IsKeyDown(EKey::S))
			transform.rotation.x -= 0.1f * _delta;

		if (keyboard->IsKeyDown(EKey::Left))
			transform.position.x -= 0.01f * _delta;
		if (keyboard->IsKeyDown(EKey::Right))
			transform.position.x += 0.01f * _delta;
		if (keyboard->IsKeyDown(EKey::Down))
			transform.position.z += 0.01f * _delta;
		if (keyboard->IsKeyDown(EKey::Up))
			transform.position.z -= 0.01f * _delta;
		if (keyboard->IsKeyDown(EKey::Space))
			transform.position.y += 0.01f * _delta;
		if (keyboard->IsKeyDown(EKey::LShift))
			transform.position.y -= 0.01f * _delta;

		if(keyboard->IsKeyDown(EKey::P))
		{
			std::cout << (S("Position : X : ") + SN(transform.position.x) + S(" - Y : ") + SN(transform.position.y) + S(" - Z : ") + SN(transform.position.z) + S("\nRotation : X : ") + SN(transform.rotation.x) + S(" - Y : ") + SN(transform.rotation.y) + S(" - Z : ") + SN(transform.rotation.z)).CStr() << std::endl;
			//LOG(S("Position : X : ") + SN(transform.position.x) + S(" - Y : ") + SN(transform.position.y) + S(" - Z : ") + SN(transform.position.z) + S("\nRotation : X : ") + SN(transform.rotation.x) + S(" - Y : ") + SN(transform.rotation.y) + S(" - Z : ") + SN(transform.rotation.z), LOG_DEBUG);
		}

		camera->SetTransform(transform);
	}
};
