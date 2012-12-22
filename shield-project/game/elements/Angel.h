#ifndef _ANGEL_H_
#define _ANGEL_H_

#include "Enemy.h"

namespace shield {
namespace game {
	class Angel : public Enemy
	{
	public:
		Angel( const structs::Point&, const structs::Vector3&, int, int );
		void update( LONGLONG );
		bool hit( const Element& ) const;
		std::vector<Mesh*> getMesh();

	private:
		int _hp;
		int _maxHp;
	};
};
};

#endif
