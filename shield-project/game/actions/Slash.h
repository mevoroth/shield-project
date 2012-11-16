#ifndef _SLASH_H_
#define _SLASH_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class Slash : public services::Action
	{
	public:
		Slash( Game* );
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
