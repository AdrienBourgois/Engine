#include "Modules/Render/RenderInterface.h"
#include "DirectX/Dx12.h"

bool Module::Render::RenderInterface::Initialize()
{
	switch (api) { case DirectX12Api : renderer = new DirectX12::DirectX12(); }

	return true;
}

bool Module::Render::RenderInterface::Start()
{
	return renderer->CreatePipeline();
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
