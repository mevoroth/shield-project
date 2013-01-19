#ifndef _ENDGAMECALLABLE_H_
#define _ENDGAMECALLABLE_H_

#include "Callable.h"
#include "..\Game.h"
#include "..\Engine.h"

namespace shield {
namespace structs {
	class EndGameCallable : public Callable
	{
	public:
		EndGameCallable( Game*, Engine* );
		void operator()( void );

	private:
		Game* _g;
		Engine* _e;
	};
};
};

#endif
