#include "LaserBeam.h"
#include "Element.h"
#include "LaserBeamBullet.h"

using namespace shield;

game::LaserBeam::LaserBeam( int damage )
	: Weapon( damage )
{
};
const std::vector<game::Element*>& game::LaserBeam::shoot(
	structs::Point* p
) const
{
	std::vector<game::Element*>* bullets = new std::vector<game::Element*>;
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
