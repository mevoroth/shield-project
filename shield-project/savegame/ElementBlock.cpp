#include "ElementBlock.h"

//using namespace shield::savegame;

istream& shield::savegame::operator>>( istream& is, ElementBlock& eb )
{
	is.read((char*)&eb.type, sizeof(ElementBlock::Type));
	is.read((char*)&eb.hp, sizeof(int));
	is.read((char*)&eb.hpmax, sizeof(int));
	is.read((char*)&eb.x, sizeof(float));
	is.read((char*)&eb.y, sizeof(float));
	is.read((char*)&eb.z, sizeof(float));
	//is.read((char*)&eb.dx, sizeof(float));
	//is.read((char*)&eb.dy, sizeof(float));
	//is.read((char*)&eb.dz, sizeof(float));
	//is.read((char*)&eb.type, sizeof(ElementBlock::Weapon));

	return is;
};
