#include "DashRight.h"
#include "..\..\structs\Vector3.h"

using namespace shield;
using namespace shield::game::actions;

DashRight::DashRight( Game* g )
	: _game( g )
{
};
void DashRight::call()
{
	_game->Dash(
		structs::Vector3(1.f, 0.f, 0.f)
	);
};
