#ifndef _MOVELEFT_H_
#define _MOVELEFT_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class MoveLeft : public services::Action
	{
	public:
		MoveLeft( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
