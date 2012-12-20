#ifndef _MOVEDOWNUP_H_
#define _MOVEDOWNUP_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class MoveDownUp : public services::Action
	{
	public:
		MoveDownUp( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
