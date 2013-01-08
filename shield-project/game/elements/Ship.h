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
		 * @param[in] Spawn*
		 * @param[in] Direction
		 * @param[in] Mesh
		 * @param[in] HP
		 * @param[in] HP Max
		 */
		Ship(
			const structs::Point&,
			const structs::Vector3&,
			const std::vector<Mesh*>&,
			int,
			int
		);
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
		virtual std::list<Element*> shoot() const = 0;
		int getHpMax( void ) const;
		int getHp( void ) const;
		virtual void damage( int );
		bool isDead() const;

	private:
		int _maxHp;
		int _hp;
	};
};
};

#endif
