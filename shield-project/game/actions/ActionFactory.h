#ifndef _ACTIONFACTORY_H_
#define _ACTIONFACTORY_H_

#include "..\..\Game.h"
#include "..\..\services\controls\Action.h"

using namespace shield;

namespace shield {
namespace game {
	class ActionFactory
	{
	public:
		static void setGame( Game* );
		static services::Action* getBurst();
		static services::Action* getCharge();
		static services::Action* getDashLeft();
		static services::Action* getDashRight();
		static services::Action* getMoveDown();
		static services::Action* getMoveLeft();
		static services::Action* getMoveRight();
		static services::Action* getMoveUp();
		static services::Action* getShield();
		static services::Action* getShoot();
		static services::Action* getSlash();

	private:
		static Game* _g;
	};
};
};

#endif
