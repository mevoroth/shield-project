#include "Ship.h"
#include "..\..\Service.h"

using namespace shield;

game::Ship::Ship(
	const structs::Point& p,
	const structs::Vector3& dir,
	const std::vector<Mesh*>& meshes,
	int hp, int maxHp
)
	: Element( p, dir, meshes ),
	_maxHp( maxHp ),
	_hp( hp )
{
};
game::Ship::Ship( const Ship& s )
	: Element( s )
{
	_hp = s._hp;
	_maxHp = s._maxHp;
};
game::Ship::~Ship()
{
};
std::list<game::Element*> game::Ship::shoot() const
{
	//TODO : Shoot
	std::list<game::Element*> bidule;
	return bidule;
};
int game::Ship::getHp( void ) const
{
	return _hp;
};
int game::Ship::getHpMax( void ) const
{
	return _maxHp;
};
void game::Ship::damage( int damage )
{
	_hp -= damage;
	if ( _hp <= 0 )
	{
		//Service::getEventsManager()->notify( HOPE_DEATH, this );
	}
};
