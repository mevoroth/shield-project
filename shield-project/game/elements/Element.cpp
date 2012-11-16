#include "Element.h"

using namespace shield;

game::Element::Element( float x, float y, float z )
	: _currentTime( 0l ),
	_spawnTime( 0l ),
	_position( structs::Point(x, y, z) )
{
};
game::Element::Element( const structs::Point& p )
	: _currentTime( 0l ),
	_spawnTime( 0l ),
	_position( structs::Point(p) )
{
};
game::Element::Element( const game::Element& e )
	: _position( structs::Point(e._position) )
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
void game::Element::refresh( void )
{
	_currentTime = GetTickCount64();
};
unsigned long long game::Element::getCurrentTime( void ) const
{
	return _currentTime;
};
unsigned long long game::Element::getSpawnTime( void ) const
{
	return _spawnTime;
};
const structs::Point& game::Element::getPosition( void ) const
{
	return _position;
};
