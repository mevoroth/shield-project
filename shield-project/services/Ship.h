#ifndef _SHIP_H_
#define _SHIP_H_

namespace shield {
	class Ship
	{
	public:
		Ship(unsigned int hp);

	private:
		Weapon* _w;
		unsigned int _hp;
	};
};

#endif
