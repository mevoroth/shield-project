#include "MoveRight.h"
#include "..\..\structs\Vector3.h"

using namespace shield;
using namespace shield::game::actions;

MoveRight::MoveRight( Game* g )
	: _game( g )
{
};
void MoveRight::call()
{
	_game->Move(
		structs::Vector3(1.f, 0.f, 0.f)
	);
};
