#ifndef _GAME_H_
#define _GAME_H_

#include <list>
//#include <boost\thread.hpp>
#include "game\elements\Element.h"
#include "game\elements\Hope.h"
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
		void render();

		/**
		 * Déplacement (forme mecha)
		 */
		void Move( const structs::Vector3& );
		/**
		 * Déplacement rapide (forme mecha)
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
		 * Frappe avec l'arme corps-à-corps (forme mecha)
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
		Hope* _player;
		std::list<Element*> _elements;
		std::list<Element*> _bullets;
		//std::list<boost::mutex> _elementsMutex;
		Hope* _getPlayer();
	};
};

#endif
