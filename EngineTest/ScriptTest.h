#pragma once

#include "Engine.h"
#include "Core/Interface/IScript.h"
#include "Objects/GameObject.h"
#include "Objects/Components/GraphicComponent.h"
#include "Modules/Render/RenderInterface.h"
#include "Modules/Inputs/Inputs.h"
#include "Modules/Time/Clock.h"

class ScriptTest : public Core::Interface::IScript
{
public:
	DECLARE_SCRIPT(S("Script Test"), Core::CoreType::SimpleScript)

	ScriptTest() = default;
	~ScriptTest() = default;

	Object::GameObject* go[9];

	void Start() override
	{
		for (unsigned int i = 0; i < 9; ++i)
		{
			go[i] = new Object::GameObject(S("GameObject"));
			Object::Component::GraphicComponent* graphics = go[i]->CreateComponent<Object::Component::GraphicComponent>(Core::CoreType::PrimitiveMesh::PrimitivesMeshType::Cube);
			MODULE(Module::Render::RenderInterface)->CreateBuffer(graphics);
		}
	}

	void Update() override
	{
		float delta = MODULE(Module::Clock)->GetDeltaTime();
		Core::CoreType::Time time = MODULE(Module::Clock)->GetTotalTime();

		if (MODULE(Module::Inputs)->Keyboard()->IsKeyDown(Key::Escape))
			ENGINE->Stop();

		for (unsigned int i = 0; i < 3; ++i)
		{
			for (unsigned int j = 0; j < 3; ++j)
			{
				float x = static_cast<float>(i);
				float y = static_cast<float>(j);
				Core::CoreType::Transform transform = go[j + 3 * i]->GetTransform();
				transform.position.x = x - 1;
				transform.position.y = y - 1;
				transform.scale = { 0.3f, 0.3f, 0.3f };
				transform.rotation.x += (i + j) * delta / 5.f;
				go[j + 3 * i]->SetTransform(transform);
			}
		}
	}

	void Destruct() override
	{
		for (int i = 0; i < 9; ++i)
		{
			delete go[i];
		}
	}
};
