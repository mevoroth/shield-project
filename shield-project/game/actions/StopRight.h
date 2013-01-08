#ifndef _STOPRIGHT_H_
#define _STOPRIGHT_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class StopRight : public services::Action
	{
	public:
		StopRight( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
