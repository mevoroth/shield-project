#include "Weapon.h"

using namespace shield::game;

Weapon::Weapon( int damage )
	: _damage( damage )
{
};
int Weapon::getDamage( void ) const
{
	return _damage;
};
