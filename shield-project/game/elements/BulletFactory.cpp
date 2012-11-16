#include "BulletFactory.h"
#include "LaserBeamBullet.h"
#include "..\..\Settings.h"

using namespace shield::game;
using namespace shield::structs;

Element* BulletFactory::getLaserBeamBulletLv0( const Point& spawn )
{
	return new LaserBeamBullet( spawn, 1, 1,
		settings::weapons::LASER_BEAM_LV0 );
};
Element* BulletFactory::getLaserBeamBulletLv1( const Point& spawn )
{
	return new LaserBeamBullet( spawn, 1, 1,
		settings::weapons::LASER_BEAM_LV1 );
};
Element* BulletFactory::getLaserBeamBulletLv2( const Point& spawn )
{
	return new LaserBeamBullet( spawn, 1, 1,
		settings::weapons::LASER_BEAM_LV2 );
};
Element* BulletFactory::getLaserBeamBulletLvMax( const Point& spawn )
{
	return new LaserBeamBullet( spawn, 1, 1,
		settings::weapons::LASER_BEAM_LVMAX );
};

