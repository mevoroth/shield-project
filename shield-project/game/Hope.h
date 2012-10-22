#ifndef _HOPE_H_
#define _HOPE_H_

#include "Ship.h"

namespace shield {
namespace game {
	/**
	 * Espoir
	 * Vaisseau du h�ros
	 */
	class Hope : public Ship
	{
	public:
		/**
		 * Cr�e un vaisseau
		 * @param Spawn
		 * @param Arme
		 * @param HP
		 */
		Hope( structs::Point*, Weapon*, int );
		bool hit( const structs::Point* ) const;
	};
};
};

#endif
