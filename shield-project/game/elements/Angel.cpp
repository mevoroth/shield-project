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
	: Enemy(
		p,
		dir,
		Service::getMeshLoader()->load("resources\\meshes\\AlphaEnemy.fbx")
	)
{
	/*if ( _meshes == 0 )
	{
		_meshes = new std::vector<Mesh*>(
			Service::getMeshLoader()->load("resources\\meshes\\AlphaEnemy.fbx")
		);
	}*/
	_hp = hp;
	_maxHp = maxHp;
};
void Angel::update( ULONGLONG elapsedTime )
{
	Element::update( elapsedTime );
};
bool Angel::hit( const Element& e ) const
{
	return false;
};
