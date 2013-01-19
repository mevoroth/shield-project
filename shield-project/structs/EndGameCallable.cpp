#include "EndGameCallable.h"

using namespace shield::structs;

EndGameCallable::EndGameCallable( shield::Game* g, shield::Engine* e )
	: _g( g ),
	_e( e )
{
};
void EndGameCallable::operator()( void )
{
	while ( !_g->end() )
	{
		Sleep( 1000 );
	}
	_e->close();
};
