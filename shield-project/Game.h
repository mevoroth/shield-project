#ifndef _GAME_H_
#define _GAME_H_

#include <list>
#include <queue>
#include <Windows.h>
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
		enum Action
		{
			MOVE_LEFT,
			MOVE_RIGHT,
			MOVE_UP,
			MOVE_DOWN,
			DASH_LEFT,
			DASH_RIGHT,
			CHARGE,
			SHOOT,
			BURST,
			SLASH,
			SHIELD
		};
		enum
		{
			UP = 0,
			DOWN = 1,
			LEFT = 2,
			RIGHT = 3
		};
		Game( void );
		~Game( void );
		/**
		 * Charger une partie
		 */
		void load( const std::string& );
		void create( void );
		void run( void );
		void reset( void );

		void render( void );

		/**
		 * D�placement (forme mecha)
		 */
		void MoveLeft( void );
		void MoveRight( void );
		void MoveUp( void );
		void MoveDown( void );
		/**
		 * D�placement (forme mecha) stop
		 */
		void MoveLeftUp( void );
		void MoveRightUp( void );
		void MoveUpUp( void );
		void MoveDownUp( void );
		/**
		 * D�placement rapide (forme mecha)
		 */
		void DashLeft( void );
		void DashRight( void );
		/**
		 * Charge l'arme principal (forme mecha)
		 */
		void Charge( void );
		/**
		 * Tire avec l'arme principal (forme mecha)
		 */
		void Shoot( void );
		/**
		 * Tire avec l'arme secondaire (forme mecha)
		 */
		void Burst( void );
		/**
		 * Frappe avec l'arme corps-�-corps (forme mecha)
		 */
		void Slash( void );
		/**
		 * Protection (forme mecha)
		 */
		void Shield( void );
		/**
		 * Switch entre forme mecha et forme vaisseau
		 */
		void SwapForm( void );

	private:
		Hope* _player;
		std::list<Element*> _elements;
		std::list<Element*> _bullets;
		std::queue<Action> _actionsQueue;
		//std::list<boost::mutex> _elementsMutex;
		Hope* _getPlayer();
		ULONGLONG _lastTick;
		bool _moves[4];

		/**
		 * @param[in] Elapsed time
		 */
		void _input( ULONGLONG );
		/**
		 * @param[in] Elapsed time
		 */
		void _update( ULONGLONG );
		/**
		 * @param[in] Elapsed time
		 */
		void _draw( unsigned long long );
		void _drawElements( const std::list<Element*>& );
		void _drawMeshes( const std::vector<Mesh*>& );
		void _updateElements( ULONGLONG, std::list<Element*>& );
	};
};

#endif
