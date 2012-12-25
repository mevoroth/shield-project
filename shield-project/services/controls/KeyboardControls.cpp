#include <iostream>
#include <dinput.h>
#include "KeyboardControls.h"

using namespace shield;
using namespace std;

services::KeyboardControls::KeyboardControls( void )
{
	std::cout << "KeyboardControls initialized" << std::endl;
};
services::KeyboardControls::~KeyboardControls( void )
{
	for ( map<pair<WPARAM, ControlsState>, Action*>::iterator it = _binds.begin();
		it != _binds.end();
		++it )
	{
		delete it->second;
	}
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
	_binds.insert(
		pair<pair<WPARAM, ControlsState>, Action*>(
			*(pair<WPARAM, ControlsState>*)state,
			action
		)
	);
};

inline void services::KeyboardControls::_call( WPARAM key, ControlsState s )
{
	map<pair<WPARAM, ControlsState>, Action*>::const_iterator element = _binds.find(
		pair<WPARAM, ControlsState>(key, s)
	);
	if ( element != _binds.end() )
	{
		element->second->call();
	}
};
