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

	Core::CoreType::Vertex point1 = Core::CoreType::Vertex(Math::Vec3(0.f, .5f, .5f), Core::CoreType::Color::Red);
	Core::CoreType::Vertex point2 = Core::CoreType::Vertex(Math::Vec3(.25f, .0f, .5f), Core::CoreType::Color::Blue);
	Core::CoreType::Vertex point3 = Core::CoreType::Vertex(Math::Vec3(-.25f, .0f, .5f), Core::CoreType::Color::Green);

	Core::CoreType::Vertex point4 = Core::CoreType::Vertex(Math::Vec3(-.25f, .0f, .5f), Core::CoreType::Color::White);
	Core::CoreType::Vertex point5 = Core::CoreType::Vertex(Math::Vec3(.0f, -.5f, .5f), Core::CoreType::Color::Black);
	Core::CoreType::Vertex point6 = Core::CoreType::Vertex(Math::Vec3(-.5f, -.5f, .5f), Core::CoreType::Color::Red);

	Core::CoreType::Vertex point7 = Core::CoreType::Vertex(Math::Vec3(.25f, .0f, .5f), Core::CoreType::Color::Green);
	Core::CoreType::Vertex point8 = Core::CoreType::Vertex(Math::Vec3(.5f, -.5f, .5f), Core::CoreType::Color::Blue);
	Core::CoreType::Vertex point9 = Core::CoreType::Vertex(Math::Vec3(.0f, -.5f, .5f), Core::CoreType::Color::White);

	Core::CoreType::Vertex triangle[] = { point1, point2, point3 };
	Core::CoreType::Vertex triangle2[] = { point4, point5, point6 };
	Core::CoreType::Vertex triangle3[] = { point7, point8, point9 };

	Object::Component::GraphicComponent object1(triangle, 3);
	Object::Component::GraphicComponent object2(triangle2, 3);
	Object::Component::GraphicComponent object3(triangle3, 3);

	CreateBuffer(&object1);
	CreateBuffer(&object2);
	CreateBuffer(&object3);

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
	return renderer->CreateVertexBuffer(_component->GetId().GetInstanceNumber(), _component->GetPoints(), _component->GetSize(), S("WIP : Need to retrieve object name"));
}
