#ifndef _DIRECTINPUTCONTROLS_H_
#define _DIRECTINPUTCONTROLS_H_

#include <Windows.h>
#include <map>
#include "IControls.h"
#include "State.h"

namespace shield {
namespace services {
	class KeyboardControls : public IControls
	{
	public:
		KeyboardControls( void );
		~KeyboardControls( void );
		/**
		 * Pression de touche
		 * @param WPARAM* Touche
		 * @param LPARAM* Paramètres
		 */
		void keyDown( const void*, const void* );
		/**
		 * Relâchement de touche
		 * @param WPARAM* Touche
		 * @param LPARAM* Paramètres
		 */
		void keyUp( const void*, const void* );
		/**
		 * Bind une action sur touche
		 * @param Touche
		 * @param Action
		 */
		void bind( const void*, Action* );
	private:
		/**
		 * Binds
		 */
		std::map<std::pair<WPARAM, State>, Action*> _binds;
		/**
		 * Appel d'action
		 * @param Touche
		 * @param Etat de pression
		 */
		inline void _call( WPARAM, State );
	};
};
};

#endif
