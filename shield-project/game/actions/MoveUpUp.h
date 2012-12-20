#ifndef _MOVEUPUP_H_
#define _MOVEUPUP_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class MoveUpUp : public services::Action
	{
	public:
		MoveUpUp( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
