#ifndef _LASERBEAMBULLET_H_
#define _LASERBEAMBULLET_H_

#include "Element.h"
#include "..\..\structs\Point.h"

namespace shield {
namespace game {
	class LaserBeamBullet : public Element
	{
	public:
		/**
		 * @param Spawn
		 * @param Rayon
		 * @param Longueur
		 * @param D�g�ts
		 */
		LaserBeamBullet( const structs::Point& p, int, int, int );
		LaserBeamBullet( const LaserBeamBullet& );
		bool hit( const Element& ) const;
		const std::vector<Mesh*>& getMesh() const;
	private:
		/**
		 * V�rifie la collision
		 * @param Le laser
		 * @param L'objet
		 */
		bool _collide( const structs::Point&, const structs::Point& ) const;
		/**
		 * Rayon du laser (pixel)
		 */
		int _ray;
		/**
		 * Longueur du laser
		 */
		int _length;
		/**
		 * D�g�ts
		 */
		int _damage;
	};
};
};

#endif
