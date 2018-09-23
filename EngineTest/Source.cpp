#include "Engine.h"
#include "Windows.h"

#include "RedCube.h"
#include "Camera.h"

int WINAPI wWinMain(HINSTANCE _h_instance, HINSTANCE _h_prev_instance, PWSTR _p_cmd_line, int _n_cmd_show)
{
	HINSTANCE__* hinst_lib = LoadLibrary(L"EngineCore.dll");
	Engine::GetInstance()->Initialize();

	ADD_SCRIPT(RedCube);
	ADD_SCRIPT(CameraScript);

	Engine::GetInstance()->Start();

	FreeLibrary(hinst_lib);

	return EXIT_SUCCESS;
}
