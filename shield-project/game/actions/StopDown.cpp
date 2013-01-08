#include "StopDown.h"

using namespace shield::game::actions;

StopDown::StopDown( Game* g )
	: _game( g )
{
};
void StopDown::call()
{
	_game->move( Game::Direction::DOWN, false );
};
