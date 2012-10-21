#ifndef _LASERBEAMBULLET_H_
#define _LASERBEAMBULLET_H_

#include "Element.h"
#include "..\structs\Point.h"

namespace shield {
namespace game {
	class LaserBeamBullet : public Element
	{
	public:
		bool hit( const structs::Point* );
	private:
		bool _collide( const structs::Point*, const structs::Point* ) const;
	};
};
};

#endif
