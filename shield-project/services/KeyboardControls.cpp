#include <iostream>
#include <dinput.h>
#include "KeyboardControls.h"

using namespace shield;

services::KeyboardControls::KeyboardControls( HINSTANCE hInst )
{
	std::cout << "KeyboardControls initialized" << std::endl;
};
