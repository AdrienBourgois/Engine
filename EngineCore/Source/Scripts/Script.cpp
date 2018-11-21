#include "Script.h"

Scripts::Script::Script()
{
	clockModuleReference = Engine::GetInstance()->GetModule<Module::Time::Clock>();
	windowModuleReference = Engine::GetInstance()->GetModule<Module::Display::Window>();
	renderInterfaceModuleReference = Engine::GetInstance()->GetModule<Module::Render::RenderInterface>();
	loggerModuleReference = Engine::GetInstance()->GetModule<Module::Tools::Logs::Logger>();
	inputsModuleReference = Engine::GetInstance()->GetModule<Module::Inputs::Input>();
}

Module::Time::Clock* Scripts::Script::GetClock() const
{
	return clockModuleReference;
}

Module::Display::Window* Scripts::Script::GetWindow() const
{
	return windowModuleReference;
}

Module::Render::RenderInterface* Scripts::Script::GetRenderInterface() const
{
	return renderInterfaceModuleReference;
}

Module::Tools::Logs::Logger* Scripts::Script::GetLogger() const
{
	return loggerModuleReference;
}

Module::Inputs::Input* Scripts::Script::GetInputs() const
{
	return inputsModuleReference;
}
