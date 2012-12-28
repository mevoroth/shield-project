#include "Angel.h"

#include "..\..\Service.h"

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
		dir,
		Service::getMeshLoader()->load("resources\\meshes\\AlphaEnemy.fbx"),
		hp,
		maxHp
	)
{
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

	return dx*dx + dz*dz + dy*dy < 8;
};
std::list<Element*> Angel::shoot() const
{
	return std::list<Element*>();
};
