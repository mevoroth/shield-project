#ifndef _SHIELD_H_
#define _SHIELD_H_

#include "..\..\services\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class Shield : public services::Action
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
