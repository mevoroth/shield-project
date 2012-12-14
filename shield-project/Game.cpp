#include "Game.h"

#include <map>
#include <fstream>
#include "Service.h"
#include "Settings.h"
#include "game\actions\ActionFactory.h"
#include "services\controls\State.h"
#include "savegame\ElementBlock.h"

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
void Game::load( const std::string& save )
{
	//_player = s;

	ifstream savegame( save );
	if ( !savegame )
	{
		throw;
	}

	// Memory blocks
	UINT16 elementsCount = 0;
	savegame::ElementBlock element;

	// Read player
	savegame >> *_player;

	for ( UINT16 i = 0; i < elementsCount; ++i )
	{
		// Read other elements
		savegame >> element;

		Element* el;

		switch ( element.type )
		{
		case savegame::ElementBlock::ANGEL:
			el = new Angel( hp, hpmax );
			break;
		case savegame::ElementBlock::ARCHANGEL:
			el = new Archangel( hp, hpmax );
			break;
		case savegame::ElementBlock::RULER:
			el = new Ruler( hp, hpmax );
			break;
		case savegame::ElementBlock::AUTHORITY:
			el = new Authority( hp, hpmax );
			break;
		case savegame::ElementBlock::VIRTUE:
			el = new Virtue( hp, hpmax );
			break;
		case savegame::ElementBlock::DOMINION:
			el = new Dominion( hp, hpmax );
			break;
		case savegame::ElementBlock::THRONE:
			el = new Throne( hp, hpmax );
			break;
		case savegame::ElementBlock::CHERUB:
			el = new Cherub( hp, hpmax );
			break;
		case savegame::ElementBlock::SERAPH:
			el = new Seraph( hp, hpmax );
			break;
		}

		_elements.push_back( el );
	}
};
void Game::create()
{
	load(
		"test"
		/*new game::Hope(
			structs::Point( 0.f, 0.f, 0.f ),
			settings::player::BASE_LIFE
		)*/
	);
};
void Game::reset( void )
{
	// Reset
};
void Game::run( void )
{
	while ( true )
	{
		ULONGLONG currentTick = GetTickCount64();
		ULONGLONG elapsedTime = currentTick - _lastTick;
		
		_input( elapsedTime );
		_update( elapsedTime );
		_draw( elapsedTime );

		_lastTick = currentTick;
	}
};
void Game::_input( ULONGLONG elapsedTime )
{
	while ( !_actionsQueue.empty() )
	{
		Action a = _actionsQueue.front();
		_actionsQueue.pop();
		switch ( a )
		{
		case MOVE_LEFT:
			_getPlayer()->move( structs::Vector3(-1.f, 0.f, 0.f) );
			break;
		case MOVE_RIGHT:
			_getPlayer()->move( structs::Vector3(1.f, 0.f, 0.f) );
			break;
		case MOVE_UP:
			_getPlayer()->move( structs::Vector3(0.f, 1.f, 0.f) );
			break;
		case MOVE_DOWN:
			_getPlayer()->move( structs::Vector3(0.f, -1.f, 0.f) );
			break;
		case DASH_LEFT:
			_getPlayer()->dash( structs::Vector3(-1.f, 0.f, 0.f) );
			break;
		case DASH_RIGHT:
			_getPlayer()->dash( structs::Vector3(1.f, 0.f, 0.f) );
			break;
		case CHARGE:
		case SHOOT:
		case BURST:
		case SLASH:
		case SHIELD:
			break;
		}
	}
};
void Game::_update( ULONGLONG elapsedTime )
{
	// Faire avancer le vaisseau
	// Faire avancer la camera
};
void Game::_draw( ULONGLONG elapsedTime )
{
	render();
};
void Game::render()
{
	Service::getGraphics()->setCamera(
		0.f, 5.f, -5.f,
		0.f, 0.f, 0.f,
		0.f, 0.f, 1.f
	);
	Service::getGraphics()->setPerspective( DirectX::XM_PIDIV4, 16.f/9.f, .1f, 100.f );
	
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
void Game::MoveLeft()
{
	_actionsQueue.push( MOVE_LEFT );
};
void Game::MoveRight()
{
	_actionsQueue.push( MOVE_RIGHT );
};
void Game::MoveUp()
{
	_actionsQueue.push( MOVE_UP );
};
void Game::MoveDown()
{
	_actionsQueue.push( MOVE_DOWN );
};
void Game::DashLeft( void )
{
	_actionsQueue.push( DASH_LEFT );
};
void Game::DashRight( void )
{
	_actionsQueue.push( DASH_RIGHT );
};
void Game::Charge()
{
	_actionsQueue.push( CHARGE );
	//_getPlayer()->charge();
};
void Game::Shoot()
{
	_actionsQueue.push( SHOOT );
	/*_bullets.splice(
		_bullets.end(),
		_getPlayer()->shoot()
	);*/
};
void Game::Burst()
{
	_actionsQueue.push( BURST );
	/*_bullets.splice(
		_bullets.end(),
		_getPlayer()->burst()
	);*/
};
void Game::Slash()
{
	_actionsQueue.push( SLASH );
};
void Game::Shield()
{
	_actionsQueue.push( SHIELD );
};
void Game::SwapForm()
{
};
Hope* Game::_getPlayer()
{
	return _player;
};
