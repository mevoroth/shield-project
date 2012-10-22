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
		 * Crée un vaisseau
		 * @param Spawn
		 * @param Arme
		 * @param HP
		 */
		Ship( structs::Point*, Weapon*, int );
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
		const std::vector<Element*>& shoot() const;
		/**
		 * Equiper l'arme sur le vaisseau
		 * @param Arme
		 */
		void setWeapon( Weapon* );
		/**
		 * Récupérer l'arme
		 * @return Arme
		 */
		const Weapon* getWeapon() const;
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
