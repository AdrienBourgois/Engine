#pragma once

#include "Engine.h"
#include "Core/Interface/IScript.h"
#include "Objects/GameObject.h"
#include "Objects/Components/GraphicComponent.h"
#include "Modules/Render/RenderInterface.h"

class ScriptTest : public Core::Interface::IScript
{
public:
	DECLARE_SCRIPT(S("Script Test"), Core::CoreType::SimpleScript)

	ScriptTest() = default;
	~ScriptTest() = default;

	Object::GameObject* go = new Object::GameObject(S("GameObject"));

	void Start() override
	{
		Core::CoreType::Vertex quad_vertices_list[] = {
		// front face
		{ -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{  0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

		// right side face
		{  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
		{  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{  0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

		// left side face
		{ -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

		// back face
		{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
		{  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

		// top face
		{ -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
		{ 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

		// bottom face
		{  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
		{  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		};

		unsigned int quad_index_list[] = {
			// front face
			0, 1, 2, // first triangle
			0, 3, 1, // second triangle

			// left face
			4, 5, 6, // first triangle
			4, 7, 5, // second triangle

			// right face
			8, 9, 10, // first triangle
			8, 11, 9, // second triangle

			// back face
			12, 13, 14, // first triangle
			12, 15, 13, // second triangle

			// top face
			16, 17, 18, // first triangle
			16, 19, 17, // second triangle

			// bottom face
			20, 21, 22, // first triangle
			20, 23, 21, // second triangle
		};

		Object::Component::GraphicComponent* graphics = go->CreateComponent<Object::Component::GraphicComponent>(quad_vertices_list, _countof(quad_vertices_list), quad_index_list, _countof(quad_index_list));
		MODULE(Module::Render::RenderInterface)->CreateBuffer(graphics);
	}

	void Update() override
	{
		Core::CoreType::Transform transform = go->GetTransform();
		transform.position.x += 0.0001f;
		transform.rotation.x += 0.01f;
		go->SetTransform(transform);
	}

	void Destruct() override
	{
		delete go;
	}
};



