#include <Windows.h>
#include "Engine.h"

using namespace shield;

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow )
{
	Engine e = Engine( hInstance, nCmdShow );
	e.run();
	return 0;
};
