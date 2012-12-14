#ifndef _GAMECALLABLE_H_
#define _GAMECALLABLE_H_

#include "..\Game.h"
#include "Callable.h"

namespace shield {
namespace structs {
	class GameCallable : public Callable
	{
	public:
		GameCallable( Game* );
		void operator()( void );

	private:
		Game* _g;
	};
};
};

#endif
