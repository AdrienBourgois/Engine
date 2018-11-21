#include "Engine.h"
#include "Windows.h"

#include "RedCube.h"
#include "Camera.h"
#include "SimpleScene.h"
#include "Axis.h"

int WINAPI WinMain(HINSTANCE__* const _h_instance, HINSTANCE__* const _h_prev_instance, char* const _command_line, const int _command_show)
{
	HINSTANCE__* hinst_lib = LoadLibrary(L"EngineCore.dll");

	Engine* engine = Engine::GetInstance();
	engine->Initialize(_h_instance);

	//engine->AddScript<RedCube>();
	engine->AddScript<SimpleScene>();
	engine->AddScript<Axis>();

	engine->AddScript<CameraScript>();

	engine->Start();

	FreeLibrary(hinst_lib);

	return EXIT_SUCCESS;
}
