#include "ActionFactory.h"
#include "Burst.h"
#include "Charge.h"
#include "DashLeft.h"
#include "DashRight.h"
#include "MoveDown.h"
#include "MoveLeft.h"
#include "MoveRight.h"
#include "MoveUp.h"
#include "Shield.h"
#include "Shoot.h"
#include "Slash.h"

using namespace shield::game;

Game* ActionFactory::_g = 0;

void ActionFactory::setGame( Game* g )
{
	_g = g;
};
services::Action* ActionFactory::getBurst()
{
	return new actions::Burst( _g );
};
services::Action* ActionFactory::getCharge()
{
	return new actions::Charge( _g );
};
services::Action* ActionFactory::getDashLeft()
{
	return new actions::DashLeft( _g );
};
services::Action* ActionFactory::getDashRight()
{
	return new actions::DashRight( _g );
};
services::Action* ActionFactory::getMoveDown()
{
	return new actions::MoveDown( _g );
};
services::Action* ActionFactory::getMoveLeft()
{
	return new actions::MoveLeft( _g );
};
services::Action* ActionFactory::getMoveRight()
{
	return new actions::MoveRight( _g );
};
services::Action* ActionFactory::getMoveUp()
{
	return new actions::MoveUp( _g );
};
services::Action* ActionFactory::getShield()
{
	return new actions::Shield( _g );
};
services::Action* ActionFactory::getShoot()
{
	return new actions::Shoot( _g );
};
services::Action* ActionFactory::getSlash()
{
	return new actions::Slash( _g );
};
