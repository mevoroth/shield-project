#include "Game.h"
#include "game\LaserBeam.h"
#include "Service.h"
#include "Settings.h"


using namespace shield;

Game::Game( void )
{
	//Service::getControls()->bind( 
};
Game::~Game( void )
{
	for ( std::list<Element*>::iterator it = _elements.begin();
		it != _elements.end();
		++it )
	{
		delete *it;
	}
};
void Game::load( Hope* s )
{
	_elements.push_back( s );
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
	while ( true )
	{
		for ( std::list<Element*>::iterator it = _elements.begin();
			it != _elements.end();
			++it )
		{
			(*it)->refresh();
		}
	}
};
void Game::Move( const structs::Vector3& direction )
{
	// TODO: Collision
	_getPlayer()->move( direction );
};
void Game::Dash( const structs::Vector3& direction )
{
	// TODO: Collision
	_getPlayer()->dash( direction );
};
void Game::Charge()
{
	_getPlayer()->charge();
};
void Game::Shoot()
{
	_getPlayer()->shoot();
};
void Game::Burst()
{
	_getPlayer()->burst();
};
void Game::Slash()
{
	_getPlayer()->slash();
};
void Game::Shield()
{
	_getPlayer()->shield();
};
void Game::SwapForm()
{
};
Hope* Game::_getPlayer()
{
	return dynamic_cast<Hope*>( _elements.front() );
};
