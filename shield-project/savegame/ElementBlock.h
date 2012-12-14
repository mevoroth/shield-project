#ifndef _ELEMENTBLOCK_H_
#define _ELEMENTBLOCK_H_

#include <istream>

using namespace std;

namespace shield {
namespace savegame {
	class ElementBlock
	{
	public:
		enum Type
		{
			ANGEL		= 0,
			ARCHANGEL	= 1,
			RULER		= 2,
			AUTHORITY	= 3,
			VIRTUE		= 4,
			DOMINION	= 5,
			THRONE		= 6,
			CHERUB		= 7,
			SERAPH		= 8
		};
		enum Weapon
		{
		};
		friend istream& operator>>( istream&, ElementBlock& );

		Type type;
		int hp;
		int hpmax;
		Weapon weapon;
	};
	istream& operator>>( istream&, ElementBlock& );
};
};

#endif
