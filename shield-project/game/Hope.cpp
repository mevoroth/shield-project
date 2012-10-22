#include "Hope.h"

using namespace shield;

game::Hope::Hope( structs::Point* p, Weapon* w, int damage )
	: Ship( p, w, damage )
{
};
bool game::Hope::hit( const structs::Point* p ) const
{
	return false;
};
