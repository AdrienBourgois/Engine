#include "Modules/Render/RenderInterface.h"
#include "DirectX/Dx12.h"

bool Module::Render::RenderInterface::Initialize()
{
	switch (api) { case DirectX12Api : renderer = new DirectX12::DirectX12(); }

	return renderer->Initialize();
}

bool Module::Render::RenderInterface::Start()
{
	renderer->CreatePipeline();

	Core::CoreType::Vertex triangle[] = {{0.f, .5f, .5f, Core::CoreType::Color::Red}, {.25f, .0f, .5f, Core::CoreType::Color::Blue}, {-.25f, .0f, .5f, Core::CoreType::Color::Green}};
	Core::CoreType::Vertex triangle2[] = {{-.25f, .0f, .5f, Core::CoreType::Color::White}, {.0f, -.5f, .5f, Core::CoreType::Color::Black}, {-.5f, -.5f, .5f, Core::CoreType::Color::Red}};
	Core::CoreType::Vertex triangle3[] = {{.25f, .0f, .5f, Core::CoreType::Color::Green}, {.5f, -.5f, .5f, Core::CoreType::Color::Blue}, {.0f, -.5f, .5f, Core::CoreType::Color::White}};

	Object::Component::GraphicComponent object1(triangle, 3);
	Object::Component::GraphicComponent object2(triangle2, 3);
	Object::Component::GraphicComponent object3(triangle3, 3);

	CreateBuffer(&object1);
	CreateBuffer(&object2);
	CreateBuffer(&object3);

	Core::CoreType::Vertex square_vertex_list[] = {
	{ -0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
	{  0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
	{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	{  0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f } };

	unsigned int square_index_list[] = {
	0, 1, 2,
	0, 3, 1	};

	Object::Component::GraphicComponent square(square_vertex_list, 4, square_index_list, 6);

	CreateBuffer(&square);

	return true;
}

bool Module::Render::RenderInterface::Update()
{
	renderer->Render();
	return true;
}

bool Module::Render::RenderInterface::Destruct()
{
	return renderer->Cleanup();
}

bool Module::Render::RenderInterface::CreateBuffer(Object::Component::GraphicComponent* _component)
{
	objects.insert_or_assign(_component->GetId().GetInstanceNumber(), _component);
	return renderer->CreateBuffers(_component->GetId().GetInstanceNumber(), S("WIP : Need to retrieve object name"), _component->GetVertices(), _component->GetVertexCount(), _component->GetIndexs(), _component->GetIndexCount());
}
