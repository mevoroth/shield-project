#ifndef _BULLETFACTORY_H_
#define _BULLETFACTORY_H_

#include "Element.h"
#include "..\..\structs\Point.h"

namespace shield {
namespace game {
	class BulletFactory
	{
	public:
		static Element* getLaserBeamBulletLv0( const structs::Point& );
		static Element* getLaserBeamBulletLv1( const structs::Point& );
		static Element* getLaserBeamBulletLv2( const structs::Point& );
		static Element* getLaserBeamBulletLvMax( const structs::Point& );
	};
};
};

#endif
