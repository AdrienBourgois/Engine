#include "Engine.h"
#include "Windows.h"

int WINAPI wWinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, PWSTR _pCmdLine, int _nCmdShow)
{
	HINSTANCE hinstLib = LoadLibrary(L"EngineCore.dll");

	Engine::GetInstance()->Start();

	FreeLibrary(hinstLib);

	return EXIT_SUCCESS;
}
