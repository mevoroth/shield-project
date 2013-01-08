#ifndef _STOPDOWN_H_
#define _STOPDOWN_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class StopDown : public services::Action
	{
	public:
		StopDown( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
