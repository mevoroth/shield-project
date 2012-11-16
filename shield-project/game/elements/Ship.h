#ifndef _SHIP_H_
#define _SHIP_H_

#include <list>
#include "Element.h"
#include "..\weapons\Weapon.h"

namespace shield {
namespace game {
	class Ship : public Element
	{
	public:
		/**
		 * Crée un vaisseau
		 * @param Spawn
		 * @param HP
		 */
		Ship( const structs::Point&, int );
		/**
		 * Constructeur par copie
		 */
		Ship( const Ship& );
		/**
		 * Destructeur
		 */
		~Ship();
		/**
		 * Tire
		 * @return Les tirs
		 */
		virtual std::list<Element*>& shoot() const = 0;
		int getHpMax( void ) const;
		int getHp( void ) const;

	private:
		int _hpmax;
		int _hp;
	};
};
};

#endif
