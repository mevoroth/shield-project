#include "DashLeft.h"

using namespace shield::game::actions;

DashLeft::DashLeft( Game* g )
	: _game( g )
{
};
void DashLeft::call()
{
	_game->DashLeft();
};
