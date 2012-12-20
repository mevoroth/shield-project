#include "MoveDownUp.h"

using namespace shield::game::actions;

MoveDownUp::MoveDownUp( Game* g )
	: _game( g )
{
};
void MoveDownUp::call()
{
	_game->MoveDownUp();
};
