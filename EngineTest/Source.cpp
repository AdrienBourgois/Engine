#include "Windows.h"
#include "Tools/Ini/IniParser.h"

int WINAPI wWinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, PWSTR _pCmdLine, int _nCmdShow)
{
	IniParser* parser = new IniParser("config.ini");
	bool result = parser->Parse();
	float value = parser->GetFloat("Values", "life");
	delete parser;

	return EXIT_SUCCESS;
}
