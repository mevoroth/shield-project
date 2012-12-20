#include "MoveUpUp.h"

using namespace shield::game::actions;

MoveUpUp::MoveUpUp( Game* g )
	: _game( g )
{
};
void MoveUpUp::call()
{
	_game->MoveUpUp();
};
