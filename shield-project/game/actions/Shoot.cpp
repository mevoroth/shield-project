#include "Shoot.h"

using namespace shield;
using namespace shield::game::actions;

Shoot::Shoot( Game* g )
	: _game( g )
{
};
void Shoot::call()
{
	_game->Action( Game::Action::SHOOT );
};
