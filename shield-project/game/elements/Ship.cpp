#include "Ship.h"

using namespace shield;

game::Ship::Ship( const structs::Point& p, int hp )
	: Element( p ),
	_hpmax( hp ),
	_hp( hp )
{
};
game::Ship::Ship( const Ship& s )
	: Element( s )
{
	_hp = s._hp;
	_hpmax = s._hpmax;
};
game::Ship::~Ship()
{
};
std::list<game::Element*> game::Ship::shoot() const
{
	std::list<game::Element*> bidule;
	return bidule;
};
int game::Ship::getHp( void ) const
{
	return _hp;
};
int game::Ship::getHpMax( void ) const
{
	return _hpmax;
};
