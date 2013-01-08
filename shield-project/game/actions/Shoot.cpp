#include "Shoot.h"

using namespace shield::game::actions;

Shoot::Shoot( Game* g )
	: _game( g )
{
};
void Shoot::call()
{
	_game->action( Game::Action::SHOOT );
};
