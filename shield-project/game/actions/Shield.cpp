#include "Shield.h"

using namespace shield;
using namespace shield::game::actions;

Shield::Shield( Game* g )
	: _game( g )
{
};
void Shield::call()
{
	_game->Shield();
};
