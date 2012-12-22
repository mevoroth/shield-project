#ifndef _HOPE_H_
#define _HOPE_H_

#include <istream>
#include <vector>
#include <list>
#include "Ship.h"
#include "..\..\structs\Vector3.h"

using namespace std;

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
		 * @param[in] Spawn
		 * @param[in] Direction
		 * @param[in] HP
		 * @param[in] HP Max
		 * @param[in] Energie
		 * @param[in] Energie max
		 */
		Hope(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int,
			int,
			int
		);
		void refresh( void );
		bool hit( const Element& ) const;
		void move( const structs::Vector3& );
		void dash( const structs::Vector3& );
		void charge( void );
		list<Element*> shoot( void ) const;
		list<Element*> burst( void ) const;
		void slash( void );
		void shield( LONGLONG );
		int getMaxEnergy( void );
		int getEnergy( void );
		void addWeapon( Weapon* );
		void setCurrentWeapon( int );

	private:
		LONGLONG _shield;
		LONGLONG _shieldLastTick;
		int _maxEnergy;
		int _energy;
		int _accumulator;
		int _currentWeapon;
		vector<Weapon*> _weapons;
	};
};
};

#endif
