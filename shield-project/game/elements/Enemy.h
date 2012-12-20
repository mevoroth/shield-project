#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Element.h"

namespace shield {
namespace game {
	class Enemy : public Element
	{
	public:
		Enemy(
			const structs::Point&,
			const structs::Vector3&,
			const std::vector<Mesh*>&
		);
	};
};
};

#endif
