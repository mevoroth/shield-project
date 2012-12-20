#ifndef _MOVERIGHTUP_H_
#define _MOVERIGHTUP_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class MoveRightUp : public services::Action
	{
	public:
		MoveRightUp( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
