#ifndef _BURST_H_
#define _BURST_H_

#include "..\..\services\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class Burst : public services::Action
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
