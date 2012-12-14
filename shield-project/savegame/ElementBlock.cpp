#include "ElementBlock.h"

#include <Windows.h>

using namespace shield::savegame;

istream& operator>>( istream& is, ElementBlock& eb )
{
	UINT8 type;
	UINT8 weapon;

	is >> type;
	is >> eb.hp;
	is >> eb.hpmax;
	is >> weapon;
	
	eb.type = (ElementBlock::Type)type;
	eb.weapon = (ElementBlock::Weapon)weapon;

	return is;
};
