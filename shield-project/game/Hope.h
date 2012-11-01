#ifndef _HOPE_H_
#define _HOPE_H_

#include "Ship.h"
#include "..\structs\Vector3.h"

namespace shield {
namespace game {
	/**
	 * Espoir
	 * Vaisseau du héros
	 */
	class Hope : public Ship
	{
	public:
		/**
		 * Crée un vaisseau
		 * @param Spawn
		 * @param Arme
		 * @param HP
		 */
		Hope( structs::Point*, Weapon*, int );
		bool hit( const structs::Point& ) const;
		void move( const structs::Vector3& );
		void dash( const structs::Vector3& );
		void charge();
		void shoot();
		void burst();
		void slash();
		void shield();

	private:
		unsigned long long _shield;
		unsigned long long _shieldLastTick;
	};
};
};

#endif
