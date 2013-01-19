#ifndef _GAME_H_
#define _GAME_H_

#include <list>
#include <queue>
#include <Windows.h>
#include <boost\thread\mutex.hpp>
#include "game\elements\Element.h"
#include "game\elements\Hope.h"
#include "structs\Vector3.h"
#include "patterns\Observable.h"
#include "services\events\HopeAction.h"
#include "services\events\BulletAction.h"

using namespace shield::game;

namespace shield
{
	class Game :
		public Observer<HopeAction>,
		public Observer<BulletAction>
	{
	public:
		enum Action
		{
			/**
			 * Déplacement rapide (forme mecha)
			 */
			DASH_LEFT,
			DASH_RIGHT,
			/**
			 * Charge l'arme principal (forme mecha)
			 */
			CHARGE,
			/**
			 * Tire avec l'arme principal (forme mecha)
			 */
			SHOOT,
			/**
			 * Tire avec l'arme secondaire (forme mecha)
			 */
			BURST,
			/**
			 * Frappe avec l'arme corps-à-corps (forme mecha)
			 */
			SLASH,
			/**
			 * Protection (forme mecha)
			 */
			SHIELD
		};
		enum Direction
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
		void load( const std::string&, const std::string& );
		void create( void );
		void run( void );
		void reset( void );

		/**
		 * Déplacement (forme mecha)
		 */
		void move( const Direction&, bool );
		/**
		 * Action
		 */
		void action( const Action& );
		/**
		 * Switch entre forme mecha et forme vaisseau
		 */
		void SwapForm( void );

		void update( const HopeAction&, void* );
		void update( const BulletAction&, void* );

		bool end( void );

	private:
		bool _end;
		Hope* _player;
		std::list<Element*> _elements;
		std::list<Element*> _bullets;
		std::list<boost::mutex> _elementsMutexes;
		std::list<boost::mutex> _bulletsMutexes;
		std::queue<Action> _actionsQueue;
		LARGE_INTEGER _lastTick;
		bool _moves[4];
		boost::mutex _elementsMutex;
		boost::mutex _bulletsMutex;

		float _triggerEnd;

		bool _bulletReflected;

		Hope* _getPlayer();
		/**
		 * @param[in] Elapsed time
		 */
		void _input( LONGLONG );
		/**
		 * @param[in] Elapsed time
		 */
		void _update( LONGLONG );
		/**
		 * @param[in] Elapsed time
		 */
		void _draw( LONGLONG );
		void _drawElements( const std::list<Element*>& );
		void _drawMeshes( const std::vector<Mesh*>& );
		void _updateElements( LONGLONG, std::list<Element*>& );
		void _resolveCollisions( std::list<Element*>&, std::list<Element*>& );
		void _resolvePlayerCollision( void );
		void _resolveGameBorderCollision( float& ) const;
	};
	bool death_elements( const Element* );
};

#endif
