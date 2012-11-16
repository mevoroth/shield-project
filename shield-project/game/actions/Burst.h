#ifndef _BURST_H_
#define _BURST_H_

#include "..\..\services\controls\Action.h"
#include "..\..\Game.h"

using namespace shield;

namespace shield {
namespace game {
namespace actions {
	class Burst : public services::Action
	{
	public:
		Burst( Game* );
		void call( void );

	private:
		Game* _game;
	};
};
};
};

#endif
