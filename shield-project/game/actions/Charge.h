#ifndef _CHARGE_H_
#define _CHARGE_H_

#include "..\..\services\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class Charge : public services::Action
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
