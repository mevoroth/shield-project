#include "LaserBeamBullet.h"

using namespace shield;

bool game::LaserBeamBullet::hit( const structs::Point* p )
{
	double diff = getSpawnTime() - getCurrentTime();
	const structs::Point* spawn = getSpawn();
	structs::Point current(
		spawn->x,
		spawn->y + diff,
		spawn->z
	);
	// Collision
	return _collide(spawn, p);
};

bool game::LaserBeamBullet::_collide(
	const structs::Point* spawn,
	const structs::Point* p
) const
{
	return false;
};
