#ifndef _SHIP_H_
#define _SHIP_H_

#include "Element.h"
#include "Weapon.h"

namespace shield {
namespace game {
	class Ship : public Element
	{
	public:
		/**
		 * @param Spawn
		 * @param Arme
		 * @param HP
		 */
		Ship( structs::Point*, Weapon*, int );
		Ship( const Ship& );
		~Ship();
		const std::vector<Element*>& shoot() const;
		int getHpMax( void ) const;
		int getHp( void ) const;

	private:
		Weapon* _w;
		int _hpmax;
		int _hp;
	};
};
};

#endif
