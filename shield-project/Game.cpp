#include "Game.h"
#include "game\LaserBeam.h"
#include "Service.h"
#include "Settings.h"


using namespace shield;

Game::Game( void )
{
	_elements = new std::list<Element*>;
};
Game::~Game( void )
{
	for ( std::list<Element*>::iterator it = _elements->begin();
		it != _elements->end();
		++it )
	{
		delete *it;
	}
	delete _elements;
};
void Game::load( Hope* s )
{
	_elements->push_back( s );
};
void Game::create()
{
	load(
		new game::Hope(
			new structs::Point( 0.f, 0.f, 0.f ),
			new game::LaserBeam( settings::weapons::LASER_BEAM ),
			settings::player::BASE_LIFE
		)
	);
};
void Game::run()
{
	//Service::getControls();
};
