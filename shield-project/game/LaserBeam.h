#ifndef _LASERBEAM_H_
#define _LASERBEAM_H_

#include "Weapon.h"

namespace shield {
namespace game {
	class LaserBeam : public Weapon
	{
	public:
		const std::vector<Element>& shoot() const;
	};
};
};

#endif
