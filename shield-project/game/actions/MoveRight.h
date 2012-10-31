#ifndef _MOVERIGHT_H_
#define _MOVERIGHT_H_

#include "..\..\services\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class MoveRight : public services::Action
	{
	public:
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
