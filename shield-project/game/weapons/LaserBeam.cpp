#include "LaserBeam.h"
#include "..\elements\Element.h"
#include "..\elements\LaserBeamBullet.h"

using namespace shield;

game::LaserBeam::LaserBeam( int damage )
	: Weapon( damage )
{
};
std::list<game::Element*>& game::LaserBeam::shoot(
	structs::Point* p
) const
{
	std::list<game::Element*>* bullets = new std::list<game::Element*>;
	game::LaserBeamBullet* bullet = new game::LaserBeamBullet( p );
	bullet->spawn();
	bullets->push_back(bullet);
	return *bullets;
};
game::LaserBeam& game::LaserBeam::clone() const
{
	LaserBeam* w = new LaserBeam( *this );
	return *w;
};
