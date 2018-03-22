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

	return true;
}

bool Module::Render::RenderInterface::Update()
{
	renderer->SetCameraProjectionMatrix(activeCamera->GetProjectionMatrix());
	renderer->SetCameraViewMatrix(activeCamera->GetViewMatrix());
	return renderer->Render();
}

bool Module::Render::RenderInterface::Destruct()
{
	delete activeCamera;
	return renderer->Cleanup();
}

bool Module::Render::RenderInterface::CreateBuffer(Object::Component::GraphicComponent* _component) const
{
	objects->insert_or_assign(_component->GetId().GetInstanceNumber(), _component);
	return renderer->CreateBuffers(_component->GetId().GetInstanceNumber(), _component->GetComponentName(), _component->GetTransformReference(), _component->GetMesh()->GetVertices(), _component->GetMesh()->GetVertexCount(), _component->GetMesh()->GetIndexes(), _component->GetMesh()->GetIndexCount());
}

Module::Render::Camera* Module::Render::RenderInterface::GetActiveCamera() const
{
	return activeCamera;
}
