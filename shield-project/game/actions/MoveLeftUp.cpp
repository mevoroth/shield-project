#include "MoveLeftUp.h"

using namespace shield::game::actions;

MoveLeftUp::MoveLeftUp( Game* g )
	: _game( g )
{
};
void MoveLeftUp::call()
{
	_game->MoveLeftUp();
};
