#include "Slash.h"

using namespace shield;
using namespace shield::game::actions;

Slash::Slash( Game* g )
	: _game( g )
{
};
void Slash::call()
{
	_game->Slash();
};
