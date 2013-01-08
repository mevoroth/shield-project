#include "LaserBeamBullet.h"
#include "..\..\Service.h"
#include "..\..\services\events\BulletAction.h"

using namespace shield;

game::LaserBeamBullet::LaserBeamBullet(
	const structs::Point& p,
	const structs::Vector3& dir,
	int ray,
	int len,
	int damage
)
	: Element(
		p + dir,
		dir,
		Service::getMeshLoader()->load("resources/meshes/AlphaBullet.fbx")
	),
	_ray( ray ),
	_length( len ),
	_damage( damage ),
	_elapsedTime( 0l )
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
	);*/
	int beamdy = (getDirection().dy > 0 ? 1 : -1);
	int shipdy = (p.getDirection().dy > 0 ? 1 : -1);
	// Collision
	return beamdy != shipdy && _collide( getPosition(), p.getPosition() );
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
	return dx*dx + dz*dz < /*_ray*_ray*/9
		&& dy*dy < /*_length*_length*/25;
};
void game::LaserBeamBullet::update( LONGLONG elapsedTime )
{
	Element::update( elapsedTime );
	if ( _elapsedTime < 100 )
	{
		//Service::getEventsManager()->notify( BULLET_DEATH, this );
		++_elapsedTime;
	}
};
bool game::LaserBeamBullet::isDead() const
{
	return _elapsedTime == 100;
};
