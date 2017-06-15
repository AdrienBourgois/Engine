#include "Engine.h"
#include "Windows.h"

#include "RedCube.h"
#include "GreenCube.h"
#include "Parents.h"

int WINAPI wWinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, PWSTR _pCmdLine, int _nCmdShow)
{
	HINSTANCE hinstLib = LoadLibrary(L"EngineCore.dll");

	ADD_SCRIPT(RedCube);
	ADD_SCRIPT(GreenCube);
	ADD_SCRIPT(Parents);

	Engine::GetInstance()->Start();

	FreeLibrary(hinstLib);

	return EXIT_SUCCESS;
}
