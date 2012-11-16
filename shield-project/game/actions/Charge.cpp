#include "Charge.h"

using namespace shield;
using namespace shield::game::actions;

Charge::Charge( Game* g )
	: _game( g )
{
};
void Charge::call()
{
	_game->Charge();
};
