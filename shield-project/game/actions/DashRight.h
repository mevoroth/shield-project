#ifndef _DASHRIGHT_H_
#define _DASHRIGHT_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class DashRight : public services::Action
	{
	public:
		DashRight( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
