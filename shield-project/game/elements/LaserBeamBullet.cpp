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
		p,
		dir,
		Service::getMeshLoader()->load("resources/meshes/AlphaBullet.fbx")
	),
	_ray( ray ),
	_length( len ),
	_damage( damage ),
	_elapsedTime( 0l ),
	_hit( false )
{
};
game::LaserBeamBullet::LaserBeamBullet( const game::LaserBeamBullet& e )
	: Element( e )
{
};
bool game::LaserBeamBullet::hit( const Element& p )
{
	int beamdy = (getDirection().dy > 0 ? 1 : -1);
	int shipdy = (p.getDirection().dy > 0 ? 1 : -1);

	// Collision
	_hit = beamdy != shipdy && _collide( getPosition(), p.getPosition() );
	return _hit;
};
bool game::LaserBeamBullet::_collide(
	const structs::Point& bullet,
	const structs::Point& p
) const
{
	float dy = p.y - bullet.y;

	return floor(p.x + .5f) == floor(bullet.x + .5f)
		&& floor(p.z + .5f) == floor(bullet.z + .5f)
		&& abs(dy) < abs(getDirection().dy);
};
void game::LaserBeamBullet::update( LONGLONG elapsedTime )
{
	Element::update( elapsedTime );
	if ( _elapsedTime < 10 )
	{
		++_elapsedTime;
	}
};
bool game::LaserBeamBullet::isDead() const
{
	return _hit || _elapsedTime == 10;
};
