#include "Angel.h"

#include "..\..\Service.h"
#include "BulletFactory.h"

using namespace shield;
using namespace shield::game;

Angel::Angel(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int maxHp
)
	: Ship(
		p,
		structs::Vector3(0.f, 0.f, 0.f),
		Service::getMeshLoader()->load("resources\\meshes\\AlphaEnemy.fbx"),
		hp,
		maxHp
	)
{
	srand(time(0));
};
void Angel::update( LONGLONG elapsedTime )
{
	Element::update( elapsedTime );
};
bool Angel::hit( const Element& p ) const
{
	// Collision
	return /*getDirection().dy < 0 && */_collide( getPosition(), p.getPosition() );
};
bool Angel::_collide(
	const structs::Point& bullet,
	const structs::Point& p
) const
{
	float dx = p.x - bullet.x;
	float dy = p.y - bullet.y;
	float dz = p.z - bullet.z;

	return dx*dx + dz*dz + dy*dy < 16;
};
std::list<Element*> Angel::shoot() const
{
	std::list<Element*> bullets;
	if ( rand() < 0.005f*RAND_MAX )
	{
		bullets.push_back(
			BulletFactory::getAngelBullet(getPosition())
		);
	}
	return bullets;
};
