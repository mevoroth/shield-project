#include "Game.h"
#include <map>
#include "Service.h"
#include "Settings.h"
#include "game\actions\ActionFactory.h"
#include "services\controls\State.h"

using namespace std;
using namespace shield;
using namespace shield::services;

Game::Game( void )
{
	ActionFactory::setGame( this );

	// Default binding
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_LEFT, PRESSED),
		ActionFactory::getMoveLeft()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_RIGHT, PRESSED),
		ActionFactory::getMoveRight()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_UP, PRESSED),
		ActionFactory::getMoveUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_DOWN, PRESSED),
		ActionFactory::getMoveDown()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>('W', PRESSED),
		ActionFactory::getBurst()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>('Q', PRESSED),
		ActionFactory::getDashLeft()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>('D', PRESSED),
		ActionFactory::getDashRight()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>('S', PRESSED),
		ActionFactory::getShield()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>('X', PRESSED),
		ActionFactory::getCharge()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>('X', RELEASED),
		ActionFactory::getShoot()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>('C', PRESSED),
		ActionFactory::getSlash()
	);
};
Game::~Game( void )
{
	// TODO: Dealloc
};
void Game::load( Hope* s )
{
	_player = s;
	//_elements.push_back( s );
	//_elementsMutex.push_back( boost::mutex() );
};
void Game::create()
{
	load(
		new game::Hope(
			structs::Point( 0.f, 0.f, 0.f ),
			settings::player::BASE_LIFE
		)
	);
};
void Game::run()
{
	//Service::getControls();
	std::list<Element*>::iterator elIt;
	//std::list<boost::mutex>::iterator mutIt;

	while ( true )
	{
#ifdef DEBUG
		/*if ( _elements.size() != _elementsMutex.size() )
		{
			throw "Elements mal initialisés";
		}*/
#endif
		elIt = _elements.begin();
		//mutIt = _elementsMutex.begin();
		
		while ( elIt != _elements.end() )
		{
			//mutIt->lock();
			(*elIt)->refresh();
			//mutIt->unlock();

			//++mutIt;
			++elIt;
		}
	}
};
void Game::render()
{
	Service::getGraphics()->setCamera(
		-5.f, -5.f, -5.f,
		0.f, 0.f, 0.f,
		0.f, 1.f, 0.f
	);
	Service::getGraphics()->setPerspective( DirectX::XM_PIDIV4, 16.f/9.f, .1f, 10.f );
	
	std::vector<Mesh*> mesh = _player->getMesh();
	Service::getGraphics()->begin();
	for ( std::vector<Mesh*>::const_iterator it = mesh.begin();
		it != mesh.end();
		++it )
	{
		Service::getGraphics()->draw(
			&(*it)->getVertexes()[0],
			(*it)->getVertexes().size(),
			(*it)->getTexture()
		);
	}
	Service::getGraphics()->end();

	// Draw game
	// Draw HUD
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
	_bullets.splice(
		_bullets.end(),
		_getPlayer()->shoot()
	);
};
void Game::Burst()
{
	_bullets.splice(
		_bullets.end(),
		_getPlayer()->burst()
	);
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
	return _player;
};
