#include <iostream>
#include <dinput.h>
#include "KeyboardControls.h"

using namespace shield;
using namespace std;

services::KeyboardControls::KeyboardControls( void )
	: _binds( 0 )
{
	_binds = new map<pair<WPARAM, State>, Action*>;
	std::cout << "KeyboardControls initialized" << std::endl;
};
void services::KeyboardControls::keyDown( const void* key, const void* params )
{
	_call(*(WPARAM*)key, PRESSED);
};
void services::KeyboardControls::keyUp( const void* key, const void* params )
{
	_call(*(WPARAM*)key, RELEASED);
};
void services::KeyboardControls::bind( const void* state, Action* action )
{
	_binds->insert(
		pair<pair<WPARAM, State>, Action*>(
			*(pair<WPARAM, State>*)state,
			action
		)
	);
};

inline void services::KeyboardControls::_call( WPARAM key, State s )
{
	map<pair<WPARAM, State>, Action*>::const_iterator element = _binds->find(
		pair<WPARAM, State>(key, s)
	);
	if ( element != _binds->end() )
	{
		element->second->call();
	}
};
