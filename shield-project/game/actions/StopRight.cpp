#include "StopRight.h"

using namespace shield::game::actions;

StopRight::StopRight( Game* g )
	: _game( g )
{
};
void StopRight::call()
{
	_game->move( Game::Direction::RIGHT, false );
};
