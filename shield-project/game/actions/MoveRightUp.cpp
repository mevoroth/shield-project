#include "MoveRightUp.h"

using namespace shield::game::actions;

MoveRightUp::MoveRightUp( Game* g )
	: _game( g )
{
};
void MoveRightUp::call()
{
	_game->MoveRightUp();
};
