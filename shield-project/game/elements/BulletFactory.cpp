#include "BulletFactory.h"
#include "LaserBeamBullet.h"
#include "..\..\Settings.h"

using namespace shield::game;
using namespace shield::structs;

Element* BulletFactory::getLaserBeamBulletLv0( const Point& spawn )
{
	return new LaserBeamBullet(
		spawn,
		structs::Vector3(0.f, 2.f, 0.f),
		1,
		1,
		settings::weapons::LASER_BEAM_LV0
	);
};
Element* BulletFactory::getLaserBeamBulletLv1( const Point& spawn )
{
	return new LaserBeamBullet(
		spawn,
		structs::Vector3(0.f, 1.f, 0.f),
		1,
		1,
		settings::weapons::LASER_BEAM_LV1
	);
};
Element* BulletFactory::getLaserBeamBulletLv2( const Point& spawn )
{
	return new LaserBeamBullet(
		spawn,
		structs::Vector3(0.f, 1.f, 0.f),
		1,
		1,
		settings::weapons::LASER_BEAM_LV2
	);
};
Element* BulletFactory::getLaserBeamBulletLvMax( const Point& spawn )
{
	return new LaserBeamBullet(
		spawn,
		structs::Vector3(0.f, 1.f, 0.f),
		1,
		1,
		settings::weapons::LASER_BEAM_LVMAX
	);
};

