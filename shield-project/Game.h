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
		 * D�placement (forme mecha)
		 */
		void Move( const structs::Vector3& );
		/**
		 * D�placement rapide (forme mecha)
		 */
		void Dash( const structs::Vector3& );
		/**
		 * Charge l'arme principal (forme mecha)
		 */
		void Charge();
		/**
		 * Tire avec l'arme principal (forme mecha)
		 */
		void Shoot();
		/**
		 * Tire avec l'arme secondaire (forme mecha)
		 */
		void Burst();
		/**
		 * Frappe avec l'arme corps-�-corps (forme mecha)
		 */
		void Slash();
		/**
		 * Protection (forme mecha)
		 */
		void Shield();
		/**
		 * Switch entre forme mecha et forme vaisseau
		 */
		void SwapForm();

	private:
		std::list<Element*> _elements;
		Hope* _getPlayer();
	};
};

#endif
