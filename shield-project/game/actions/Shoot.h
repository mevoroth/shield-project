#ifndef _SHOOT_H_
#define _SHOOT_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class Shoot : public services::Action
	{
	public:
		Shoot( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
