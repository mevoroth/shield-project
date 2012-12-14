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
	 * Vaisseau du h�ros
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
		 * Cr�e un vaisseau
		 * @param Spawn
		 * @param Arme
		 * @param HP
		 */
		Hope( const structs::Point&, int );
		void refresh( void );
		bool hit( const Element& ) const;
		vector<Mesh*> getMesh();
		void move( const structs::Vector3& );
		void dash( const structs::Vector3& );
		void charge();
		list<Element*> shoot( void ) const;
		list<Element*> burst( void ) const;
		void slash();
		void shield();
		int getMaxEnergy();
		int getEnergy();
		friend istream& operator>>( istream&, Hope& );

	private:
		ULONGLONG _shield;
		ULONGLONG _shieldLastTick;
		int _maxEnergy;
		int _energy;
		int _accumulator;
		int _currentWeapon;
		vector<Weapon> _weapons;

		vector<Mesh*> _meshes;
	};
	istream& operator>>( istream&, Hope& );
};
};

#endif
