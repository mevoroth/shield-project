#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <list>
#include "..\elements\Element.h"
#include "..\..\patterns\Cloneable.h"

namespace shield {
namespace game {
	class Weapon : public patterns::Cloneable<Weapon>
	{
	public:
		Weapon( int );
		int getDamage( void ) const;
		virtual std::list<Element*> shoot( const structs::Point& ) const = 0;

	private:
		int _damage;
	};
};
};

#endif
