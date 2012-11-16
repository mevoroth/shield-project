#include "MoveUp.h"
#include "..\..\structs\Vector3.h"

using namespace shield;
using namespace shield::game::actions;

MoveUp::MoveUp( Game* g )
	: _game( g )
{
};
void MoveUp::call()
{
	_game->Move(
		structs::Vector3(0.f, 0.f, 1.f)
	);
};
