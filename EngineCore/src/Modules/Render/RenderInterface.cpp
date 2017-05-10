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

	Core::CoreType::Vertex quad1[] = {
	{ -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	{  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	{  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f }
	};

	Core::CoreType::Vertex quad2[] = {
	{ -0.75f,  0.75f, 0.7f, 0.0f, 1.0f, 0.0f, 1.0f },
	{   0.0f,  0.0f,  0.7f, 0.0f, 1.0f, 0.0f, 1.0f },
	{ -0.75f,  0.0f,  0.7f, 0.0f, 1.0f, 0.0f, 1.0f },
	{   0.0f,  0.75f, 0.7f, 0.0f, 1.0f, 0.0f, 1.0f }
	};

	unsigned int square_index_list[] = {
	0, 1, 2,
	0, 3, 1	};

	Object::Component::GraphicComponent square1(quad1, 4, square_index_list, 6);
	Object::Component::GraphicComponent square2(quad2, 4, square_index_list, 6);

	CreateBuffer(&square1);
	CreateBuffer(&square2);

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
