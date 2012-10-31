#include "MoveDown.h"
#include "..\..\structs\Vector3.h"

using namespace shield;
using namespace shield::game::actions;

void MoveDown::call()
{
	_game->Move(
		structs::Vector3(0.f, 0.f, -1.f)
	);
};
