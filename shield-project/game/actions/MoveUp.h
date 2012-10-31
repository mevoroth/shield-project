#ifndef _MOVEUP_H_
#define _MOVEUP_H_

#include "..\..\services\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class MoveUp : public services::Action
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
