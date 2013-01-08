#ifndef _STOPUP_H_
#define _STOPUP_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class StopUp : public services::Action
	{
	public:
		StopUp( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
