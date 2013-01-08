#include "MoveUp.h"

using namespace shield::game::actions;

MoveUp::MoveUp( Game* g )
	: _game( g )
{
};
void MoveUp::call()
{
	_game->move( Game::Direction::UP, true );
};
