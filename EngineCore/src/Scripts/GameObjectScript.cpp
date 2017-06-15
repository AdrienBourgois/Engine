#include "GameObjectScript.h"

Scripts::GameObjectScript::GameObjectScript()
{}

void Scripts::GameObjectScript::MakeMesh(PrimitiveMesh::PrimitivesMeshType _mesh)
{
	Object::Component::GraphicComponent* graphics = object.CreateComponent<Object::Component::GraphicComponent>(_mesh);
	MODULE(Module::Render::RenderInterface)->CreateBuffer(graphics);
}
