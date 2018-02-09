#include "Script.h"

Scripts::Script::Script()
{
	clockModuleReference = MODULE(Module::Time::Clock);
	windowModuleReference = MODULE(Module::Display::Window);
	renderInterfaceModuleReference = MODULE(Module::Render::RenderInterface);
	loggerModuleReference = MODULE(Module::Tools::Logs::Logger);
	inputsModuleReference = MODULE(Module::Inputs::Input);
}

Module::Time::Clock* Scripts::Script::getClock() const
{
	return clockModuleReference;
}

Module::Display::Window* Scripts::Script::getWindow() const
{
	return windowModuleReference;
}

Module::Render::RenderInterface* Scripts::Script::getRenderInterface() const
{
	return renderInterfaceModuleReference;
}

Module::Tools::Logs::Logger* Scripts::Script::getLogger() const
{
	return loggerModuleReference;
}

Module::Inputs::Input* Scripts::Script::getInputs() const
{
	return inputsModuleReference;
}
