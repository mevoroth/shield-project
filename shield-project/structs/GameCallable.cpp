#include "GameCallable.h"

using namespace shield::structs;

GameCallable::GameCallable( shield::Game* g )
{
	_g = g;
};
void GameCallable::operator()( void )
{
	_g->run();
};
