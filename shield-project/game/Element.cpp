#include "Element.h"

using namespace shield;

game::Element::Element( float x, float y, float z )
	: _currentTime( 0. ),
	_spawnTime( 0. )
{
	_spawn = new structs::Point(x, y, z);
};
game::Element::Element( structs::Point* p )
	: _currentTime( 0. ),
	_spawnTime( 0. )
{
	_spawn = p;
};
game::Element::Element( const game::Element& e )
	: _spawn( 0 )
{
	_spawn = new structs::Point( *(e._spawn) );
	_spawnTime = e._spawnTime;
	_currentTime = e._currentTime;
};
game::Element::~Element()
{
	delete _spawn;
};
void game::Element::spawn( double time )
{
	_spawnTime = time;
	_currentTime = time;
};
void game::Element::refresh( double time )
{
	_currentTime = time;
};
