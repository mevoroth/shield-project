#include "MoveLeft.h"
#include "..\..\structs\Vector3.h"

using namespace shield;
using namespace shield::game::actions;

void MoveLeft::call()
{
	_game->Move(
		structs::Vector3(-1.f, 0.f, 0.f)
	);
};
