#ifndef _MOVELEFTUP_H_
#define _MOVELEFTUP_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class MoveLeftUp : public services::Action
	{
	public:
		MoveLeftUp( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
