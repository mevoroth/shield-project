#include "LaserBeamBullet.h"

using namespace shield;

game::LaserBeamBullet::LaserBeamBullet( const structs::Point& p, int ray,
									   int len, int damage )
	: Element( p ),
	_ray( ray ),
	_length( len ),
	_damage( damage )
{
};
game::LaserBeamBullet::LaserBeamBullet( const game::LaserBeamBullet& e )
	: Element( e )
{
};
bool game::LaserBeamBullet::hit( const Element& p ) const
{
	/*unsigned long long diff = getSpawnTime() - getCurrentTime();
	const structs::Point& spawn = getSpawn();
	structs::Point current(
		spawn.x,
		spawn.y + diff,
		spawn.z
	);
	// Collision
	return _collide(current, p);*/
	return false;
};
const std::vector<Mesh*>& game::LaserBeamBullet::getMesh() const
{
	std::vector<Mesh*> truc;
	return truc;
};
bool game::LaserBeamBullet::_collide(
	const structs::Point& bullet,
	const structs::Point& p
) const
{
	float dx = p.x - bullet.x;
	float dy = p.y - bullet.y;
	float dz = p.z - bullet.z;
	// Vérifie si l'objet est dans le rayon et
	// si l'objet se trouve dans la longueur du laser
	// TODO: Check optimisation multiplication vs comparaison
	return dx*dx + dz*dz < _ray*_ray
		&& dy*dy < _length*_length;
};
