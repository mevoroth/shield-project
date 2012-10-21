#include "LaserBeam.h"
#include "Element.h"
#include "LaserBeamBullet.h"

using namespace shield;

const std::vector<game::Element*>& game::LaserBeam::shoot(
	structs::Point* p
) const
{
	std::vector<game::Element*> bullets;
	game::LaserBeamBullet* bullet = new game::LaserBeamBullet( p );
	bullet->spawn();
	bullets.push_back(bullet);
	return bullets;
};
