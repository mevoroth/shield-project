#ifndef _ANGEL_H_
#define _ANGEL_H_

#include "Ship.h"

namespace shield {
namespace game {
	class Angel : public Ship
	{
	public:
		Angel( const structs::Point&, int, int );
		void update( LONGLONG );
		bool hit( const Element& );
		std::vector<Mesh*> getMesh();
		std::list<Element*> shoot() const;

	private:
		/**
		 * Vérifie la collision
		 * @param L'Ange
		 * @param L'objet
		 */
		bool _collide( const structs::Point&, const structs::Point& ) const;
	};
};
};

#endif
