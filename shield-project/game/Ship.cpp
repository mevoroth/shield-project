#include "Ship.h"

using namespace shield;

game::Ship::Ship( structs::Point* p, Weapon* w, int hp )
	: Element( p ),
	_w( w ),
	_hpmax( hp ),
	_hp( hp )
{
};
game::Ship::Ship( const Ship& s )
	: Element( s ),
	_w( 0 )
{
	_hp = s._hp;
	_hpmax = s._hpmax;
	_w = &s._w->clone();
};
game::Ship::~Ship()
{
	delete _w;
};
const std::vector<game::Element*>& game::Ship::shoot() const
{
	return _w->shoot( &getSpawn()->clone() );
};
void game::Ship::setWeapon( Weapon* w )
{
	if (!_w)
	{
		delete _w;
	}
	_w = w;
};
const game::Weapon* game::Ship::getWeapon() const
{
	return _w;
};
int game::Ship::getHp( void ) const
{
	return _hp;
};
int game::Ship::getHpMax( void ) const
{
	return _hpmax;
};
