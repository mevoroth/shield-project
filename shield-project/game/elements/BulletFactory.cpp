#include "BulletFactory.h"
#include "LaserBeamBullet.h"
#include "..\..\Settings.h"
#include "..\..\Service.h"

using namespace shield;
using namespace shield::game;
using namespace shield::structs;

shield::Game* BulletFactory::_g = 0;

void BulletFactory::setGame( Game* g )
{
	_g = g;
};
Element* BulletFactory::getLaserBeamBulletLv0( const Point& spawn )
{
	if ( _g == 0 )
	{
		throw;
	}
	LaserBeamBullet* bullet = new LaserBeamBullet(
		spawn,
		structs::Vector3(0.f, 2.f, 0.f),
		1,
		1,
		settings::weapons::LASER_BEAM_LV0
	);
	Service::getEventsManager()->bind( BULLET_DEATH, _g );
	return bullet;
};
Element* BulletFactory::getLaserBeamBulletLv1( const Point& spawn )
{
	if ( _g == 0 )
	{
		throw;
	}
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
	if ( _g == 0 )
	{
		throw;
	}
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
	if ( _g == 0 )
	{
		throw;
	}
	return new LaserBeamBullet(
		spawn,
		structs::Vector3(0.f, 1.f, 0.f),
		1,
		1,
		settings::weapons::LASER_BEAM_LVMAX
	);
};

