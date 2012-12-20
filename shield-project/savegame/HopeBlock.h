#ifndef _HOPEBLOCK_H_
#define _HOPEBLOCK_H_

#include <istream>

using namespace std;

namespace shield {
namespace savegame {
	class HopeBlock
	{
	public:
		enum Weapon
		{
			W_NOWEAPON		= 0x0,
			W_GANDIVA		= 0x1,
			W_THEGADGET		= 0x2,
			W_YATANOKAGAMI	= 0x4,
			W_GUNGNIR		= 0x8,
			W_VAJRA			= 0x10,
			W_CADUCEUS		= 0x20,
			W_WHITEFANG		= 0x40,
			W_MASAMUNE		= 0x80,
			W_MURASAMA		= 0x100,
			W_SOLAIS		= 0x200,
			W_AIGNE			= 0x400,
			W_CHAOS			= 0x800
		};
		friend istream& operator>>( istream&, HopeBlock& );

		float x;
		float y;
		float z;
		float dx;
		float dy;
		float dz;
		int hp;
		int maxHp;
		int maxEnergy;
		int energy;
		int currentWeapon;
		Weapon weapon;
	};
	istream& operator>>( istream&, HopeBlock& );
};
};

#endif
