#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <vector>
#include "Element.h"
#include "..\patterns\Cloneable.h"

namespace shield {
namespace game {
	class Weapon : public patterns::Cloneable<Weapon>
	{
	public:
		Weapon( int );
		int getDamage( void ) const;
		virtual const std::vector<Element*>& shoot( structs::Point* ) const = 0;

	private:
		int _damage;
	};
};
};

#endif
