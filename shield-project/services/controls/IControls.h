#ifndef _ICONTROLS_H_
#define _ICONTROLS_H_

#include "Action.h"

namespace shield {
namespace services {
	class IControls
	{
	public:
		/**
		 * Pression de touche
		 * @param Touche
		 * @param Paramètres
		 */
		virtual void keyDown( const void*, const void* ) = 0;
		/**
		 * Relâchement de touche
		 * @param Touche
		 * @param Paramètres
		 */
		virtual void keyUp( const void*, const void* ) = 0;
		/**
		 * Bind une action sur touche
		 * @param Touche
		 * @param Action
		 */
		virtual void bind( const void*, Action* ) = 0;
	};
};
};

#endif
