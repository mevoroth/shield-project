#include "Element.h"

using namespace shield;

game::Element::Element(
	float x, float y, float z,
	const structs::Vector3& direction,
	const std::vector<Mesh*>& meshes
)
	: _currentTime( 0l ),
	_spawnTime( 0l ),
	_position( structs::Point(x, y, z) ),
	_direction( direction ),
	_meshes( meshes )
{
	for ( std::vector<Mesh*>::iterator it = _meshes.begin();
		it != _meshes.end();
		++it )
	{
		**it += structs::Vector3(
			_position.x,
			_position.y,
			_position.z
			);
	}
};
game::Element::Element(
	const structs::Point& p,
	const structs::Vector3& direction,
	const std::vector<Mesh*>& meshes
)
	: _currentTime( 0l ),
	_spawnTime( 0l ),
	_position( p ),
	_direction( direction ),
	_meshes( meshes )
{
	for ( std::vector<Mesh*>::iterator it = _meshes.begin();
		it != _meshes.end();
		++it )
	{
		**it += structs::Vector3(
			_position.x,
			_position.y,
			_position.z
			);
	}
};
game::Element::Element( const game::Element& e )
	: _position( e._position ),
	_direction( e._direction ),
	_meshes( e._meshes )
{
	_spawnTime = e._spawnTime;
	_currentTime = e._currentTime;
};
game::Element::~Element()
{
};
void game::Element::spawn( void )
{
	_spawnTime = GetTickCount64();
	_currentTime = _spawnTime;
};
void game::Element::update( ULONGLONG elapsedTime )
{
	_currentTime = GetTickCount64();
	_position += _direction;
	for ( std::vector<Mesh*>::iterator it = _meshes.begin();
		it != _meshes.end();
		++it )
	{
		**it += _direction;
	}
};
unsigned long long game::Element::getCurrentTime( void ) const
{
	return _currentTime;
};
unsigned long long game::Element::getSpawnTime( void ) const
{
	return _spawnTime;
};
structs::Point game::Element::getPosition( void ) const
{
	return _position;
};
void game::Element::_moveTo( const structs::Point& p )
{
	_position = p;
};
std::vector<Mesh*> game::Element::getMesh()
{
	return _meshes;
};
