#include "DashRight.h"

using namespace shield::game::actions;

DashRight::DashRight( Game* g )
	: _game( g )
{
};
void DashRight::call()
{
	_game->DashRight();
};
