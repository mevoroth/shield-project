#ifndef _BULLETFACTORY_H_
#define _BULLETFACTORY_H_

#include "Element.h"
#include "..\..\structs\Point.h"
#include "..\..\Game.h"

namespace shield {
namespace game {
	class BulletFactory
	{
	public:
		static void setGame( Game* );
		static Element* getLaserBeamBulletLv0( const structs::Point& );
		static Element* getLaserBeamBulletLv1( const structs::Point& );
		static Element* getLaserBeamBulletLv2( const structs::Point& );
		static Element* getLaserBeamBulletLvMax( const structs::Point& );
		static Element* getAngelBullet( const structs::Point& );

	private:
		static Game* _g;
	};
};
};

#endif
