#ifndef _LASERBEAM_H_
#define _LASERBEAM_H_

#include "Weapon.h"

namespace shield {
namespace game {
	class LaserBeam : public Weapon
	{
	public:
		LaserBeam( int );
		LaserBeam& clone() const;
		std::list<Element*>& shoot( structs::Point* ) const;
	};
};
};

#endif
