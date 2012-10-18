#include <Windows.h>
#include "Engine.h"

#include <iostream>

using namespace shield;
/*
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Engine e = Engine();
	e.run();
	return 0;
};
*/
int main()
{
	Engine e;
	e.run();
	system("pause");
	return 0;
}
