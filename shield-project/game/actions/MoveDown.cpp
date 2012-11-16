#include "MoveDown.h"
#include "..\..\structs\Vector3.h"

using namespace shield;
using namespace shield::game::actions;

MoveDown::MoveDown( Game* g )
	: _game( g )
{
};
void MoveDown::call()
{
	_game->Move(
		structs::Vector3(0.f, 0.f, -1.f)
	);
};
