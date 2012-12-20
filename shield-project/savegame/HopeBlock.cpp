#include "HopeBlock.h"

istream& shield::savegame::operator>>( istream& is, HopeBlock& h )
{
	if( is.fail() )
	{
		throw;
	}
	is.read((char*)&h.x, sizeof(float));
	is.read((char*)&h.y, sizeof(float));
	is.read((char*)&h.z, sizeof(float));
	is.read((char*)&h.dx, sizeof(float));
	is.read((char*)&h.dy, sizeof(float));
	is.read((char*)&h.dz, sizeof(float));
	is.read((char*)&h.hp, sizeof(int));
	is.read((char*)&h.maxHp, sizeof(int));
	is.read((char*)&h.energy, sizeof(int));
	is.read((char*)&h.maxEnergy, sizeof(int));
	is.read((char*)&h.weapon, sizeof(HopeBlock::Weapon));
	is.read((char*)&h.currentWeapon, sizeof(int));

	return is;
};
