#include "StopUp.h"

using namespace shield::game::actions;

StopUp::StopUp( Game* g )
	: _game( g )
{
};
void StopUp::call()
{
	_game->move( Game::Direction::UP, false );
};
