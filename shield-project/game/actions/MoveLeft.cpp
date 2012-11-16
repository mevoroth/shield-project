#include "MoveLeft.h"
#include "..\..\structs\Vector3.h"

using namespace shield;
using namespace shield::game::actions;

MoveLeft::MoveLeft( Game* g )
	: _game( g )
{
};
void MoveLeft::call()
{
	_game->Move(
		structs::Vector3(-1.f, 0.f, 0.f)
	);
};
