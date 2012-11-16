#ifndef _HOPE_H_
#define _HOPE_H_

#include <vector>
#include <list>
#include "Ship.h"
#include "..\..\structs\Vector3.h"

namespace shield {
namespace game {
	/**
	 * Espoir
	 * Vaisseau du héros
	 */
	class Hope : public Ship
	{
	public:
		enum
		{
			SHIELD_TIMEOUT = 1000l,
			DEFAULT_MAX_ENERGY = 100,
			DEFAULT_ENERGY = 100,
			LV_0_CHARGE = 1,
			LV_1_CHARGE = 10,
			LV_2_CHARGE = 25,
			LV_MAX_CHARGE = 50
		};
		/**
		 * Crée un vaisseau
		 * @param Spawn
		 * @param Arme
		 * @param HP
		 */
		Hope( const structs::Point&, int );
		void refresh( void );
		bool hit( const Element& ) const;
		void move( const structs::Vector3& );
		void dash( const structs::Vector3& );
		void charge();
		std::list<Element*>& shoot( void ) const;
		std::list<Element*>& burst( void ) const;
		void slash();
		void shield();
		int getMaxEnergy();
		int getEnergy();

	private:
		unsigned long long _shield;
		unsigned long long _shieldLastTick;
		int _maxEnergy;
		int _energy;
		int _accumulator;
		int _currentWeapon;
		std::vector<Weapon> _weapons;
	};
};
};

#endif
