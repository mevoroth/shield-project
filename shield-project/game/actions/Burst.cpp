#include "Burst.h"

using namespace shield::game::actions;

Burst::Burst( Game* g )
	: _game( g )
{
};
void Burst::call( void )
{
	_game->action( Game::Action::BURST );
};
