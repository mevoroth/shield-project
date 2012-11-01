#ifndef _DASHLEFT_H_
#define _DASHLEFT_H_

#include "..\..\services\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class DashLeft : public services::Action
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
