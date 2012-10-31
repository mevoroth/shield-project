#ifndef _GAME_H_
#define _GAME_H_

#include <list>
#include "game\Element.h"
#include "game\Hope.h"
#include "structs\Vector3.h"

using namespace shield::game;

namespace shield
{
	class Game
	{
	public:
		Game( void );
		~Game( void );
		/**
		 * Charger une partie
		 */
		void load( Hope* );
		void create();
		void run();

		void Move( const structs::Vector3& );

	private:
		std::list<Element*>* _elements;
	};
};

#endif
