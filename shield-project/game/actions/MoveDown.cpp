#include "MoveDown.h"

using namespace shield::game::actions;

MoveDown::MoveDown( Game* g )
	: _game( g )
{
};
void MoveDown::call()
{
	_game->move( Game::Direction::DOWN, true );
};
