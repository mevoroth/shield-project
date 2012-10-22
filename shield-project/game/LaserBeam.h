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
		const std::vector<Element*>& shoot( structs::Point* ) const;
	};
};
};

#endif
