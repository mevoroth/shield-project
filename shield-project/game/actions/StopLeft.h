#ifndef _STOPLEFT_H_
#define _STOPLEFT_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class StopLeft : public services::Action
	{
	public:
		StopLeft( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
