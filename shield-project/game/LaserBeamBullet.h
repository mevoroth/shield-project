#ifndef _LASERBEAMBULLET_H_
#define _LASERBEAMBULLET_H_

#include "Element.h"
#include "..\structs\Point.h"

namespace shield {
namespace game {
	class LaserBeamBullet : public Element
	{
	public:
		enum {
			/**
			 * Rayon du laser (pixel)
			 */
			RAY = 5,
			/**
			 * Longueur du laser
			 */
			LENGTH = 10
		};
		LaserBeamBullet( structs::Point* p );
		LaserBeamBullet( const LaserBeamBullet& );
		bool hit( const structs::Point* ) const;
	private:
		/**
		 * Vérifie la collision
		 * @param Le laser
		 * @param L'objet
		 */
		bool _collide( const structs::Point*, const structs::Point* ) const;
	};
};
};

#endif
