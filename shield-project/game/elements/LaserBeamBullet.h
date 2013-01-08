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
		 * @param[in] Spawn
		 * @param[in] Direction
		 * @param[in] Rayon
		 * @param[in] Longueur
		 * @param[in] Dégâts
		 */
		LaserBeamBullet(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int,
			int
		);
		LaserBeamBullet( const LaserBeamBullet& );
		bool hit( const Element& ) const;
		std::vector<Mesh*> getMesh();
		bool isDead() const;
		void update( LONGLONG );

	private:
		/**
		 * Rayon du laser (pixel)
		 */
		int _ray;
		/**
		 * Longueur du laser
		 */
		int _length;
		/**
		 * Dégâts
		 */
		int _damage;
		LONGLONG _elapsedTime;

		/**
		 * Vérifie la collision
		 * @param Le laser
		 * @param L'objet
		 */
		bool _collide( const structs::Point&, const structs::Point& ) const;
	};
};
};

#endif
