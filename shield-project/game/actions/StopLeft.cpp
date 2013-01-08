#include "StopLeft.h"

using namespace shield::game::actions;

StopLeft::StopLeft( Game* g )
	: _game( g )
{
};
void StopLeft::call()
{
	_game->move( Game::Direction::LEFT, false );
};
