#include "Element.h"
#include <limits>

using namespace shield;

game::Element::Element(
	float x, float y, float z,
	const structs::Vector3& direction,
	const std::vector<Mesh*>& meshes
)
	: _position( structs::Point(x, y, z) ),
	_direction( direction ),
	_meshes( meshes )
{
	structs::Vector3 v(
		x,
		y,
		z
	);
	for ( std::vector<Mesh*>::iterator it = _meshes.begin();
		it != _meshes.end();
		++it )
	{
		**it += v;
	}
};
game::Element::Element(
	const structs::Point& p,
	const structs::Vector3& direction,
	const std::vector<Mesh*>& meshes
)
	: _position( p ),
	_direction( direction ),
	_meshes( meshes )
{
	structs::Vector3 v(
		p.x,
		p.y,
		p.z
	);
	for ( std::vector<Mesh*>::iterator it = _meshes.begin();
		it != _meshes.end();
		++it )
	{
		**it += v;
	}
};
game::Element::Element( const game::Element& e )
	: _position( e._position ),
	_direction( e._direction ),
	_meshes( e._meshes )
{
};
game::Element::~Element()
{
};
void game::Element::update( LONGLONG elapsedTime )
{
	_position += _direction;
	for ( std::vector<Mesh*>::iterator it = _meshes.begin();
		it != _meshes.end();
		++it )
	{
		**it += _direction;
	}
};
bool game::Element::isVisible( const structs::Point& p )
{
	return _position.y < p.y + 50.f && p.y < _position.y;
};
structs::Point game::Element::getPosition( void ) const
{
	return _position;
};
structs::Vector3 game::Element::getDirection( void ) const
{
	return _direction;
};
void game::Element::_moveTo( const structs::Point& p )
{
	_position = p;
};
std::vector<Mesh*>* game::Element::getMesh()
{
	return &_meshes;
};
