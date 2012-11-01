#include "Hope.h"

using namespace shield;

game::Hope::Hope( structs::Point* p, Weapon* w, int damage )
	: Ship( p, w, damage ),
	_shield( 0l ),
	_shieldLastTick( 0l )
{
};
bool game::Hope::hit( const structs::Point& p ) const
{
	return false;
};
void game::Hope::move( const structs::Vector3& direction )
{
};
void game::Hope::dash( const structs::Vector3& direction )
{
};
void game::Hope::charge()
{
};
void game::Hope::shoot()
{
};
void game::Hope::burst()
{
};
void game::Hope::slash()
{
};
void game::Hope::shield()
{
	_shieldLastTick = GetTickCount64();
	if (_shield == 0)
	{
		_shield = _shieldLastTick;
	}
};
