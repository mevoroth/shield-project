#include "MoveLeft.h"

using namespace shield::game::actions;

MoveLeft::MoveLeft( Game* g )
	: _game( g )
{
};
void MoveLeft::call()
{
	_game->MoveLeft();
};
