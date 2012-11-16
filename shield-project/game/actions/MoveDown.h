#ifndef _MOVEDOWN_H_
#define _MOVEDOWN_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class MoveDown : public services::Action
	{
	public:
		MoveDown( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
