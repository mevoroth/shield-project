#ifndef _SHOOT_H_
#define _SHOOT_H_

#include "..\..\services\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class Shoot : public services::Action
	{
	public:
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
