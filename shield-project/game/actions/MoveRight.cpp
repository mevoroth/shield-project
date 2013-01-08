#include "MoveRight.h"

using namespace shield::game::actions;

MoveRight::MoveRight( Game* g )
	: _game( g )
{
};
void MoveRight::call()
{
	_game->move( Game::Direction::RIGHT, true );
};
