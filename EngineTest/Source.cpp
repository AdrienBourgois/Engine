#include "Engine.h"
#include "Windows.h"

#include "RedCube.h"
#include "Camera.h"

int WINAPI wWinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, PWSTR _pCmdLine, int _nCmdShow)
{
	HINSTANCE hinst_lib = LoadLibrary(L"EngineCore.dll");
	Engine::GetInstance()->Initialize();

	ADD_SCRIPT(RedCube);
	ADD_SCRIPT(CameraScript);

	Engine::GetInstance()->Start();

	FreeLibrary(hinst_lib);

	return EXIT_SUCCESS;
}
