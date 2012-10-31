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

		/**
		 * Déplacement
		 */
		void Move( const structs::Vector3& );
		/**
		 * Déplacement rapide
		 */
		void Dash( const structs::Vector3& );
		/**
		 * Charge l'arme principal
		 */
		void Charge();
		/**
		 * Tire avec l'arme principal
		 */
		void Shoot();
		/**
		 * Tire avec l'arme secondaire
		 */
		void Burst();
		/**
		 * Frappe avec l'arme corps-à-corps
		 */
		void Slash();
		/**
		 * Protection
		 */
		void Shield();

	private:
		std::list<Element*> _elements;
	};
};

#endif
