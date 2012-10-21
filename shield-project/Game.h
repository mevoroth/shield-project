#ifndef _GAME_H_
#define _GAME_H_

#include <list>
#include "game\Element.h"

using namespace game;

namespace shield {
	class Game
	{
	public:
		Game( void );
		~Game( void );
		/**
		 * Charger une partie
		 */
		void load();

	private:
		std::list<Element*>* _elements;
	};
};

#endif
