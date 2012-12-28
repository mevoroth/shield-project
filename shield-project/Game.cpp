#include "Game.h"

#include <map>
#include <fstream>
#include "Service.h"
#include "Settings.h"
#include "game\actions\ActionFactory.h"
#include "services\controls\ControlsState.h"
#include "game\elements\ElementFactory.h"
#include "game\elements\BulletFactory.h"
#include "savegame\ElementBlock.h"
#include "savegame\HopeBlock.h"

using namespace std;
using namespace shield;
using namespace shield::services;
using namespace shield::savegame;

Game::Game( void )
	: _bulletReflected( false )
{
	ActionFactory::setGame( this );
	BulletFactory::setGame( this );
	//ElementFactory::setGame( this );

	// Default binding
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_LEFT, PRESSED),
		ActionFactory::getMoveLeft()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_LEFT, RELEASED),
		ActionFactory::getMoveLeftUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_RIGHT, PRESSED),
		ActionFactory::getMoveRight()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_RIGHT, RELEASED),
		ActionFactory::getMoveRightUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_UP, PRESSED),
		ActionFactory::getMoveUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_UP, RELEASED),
		ActionFactory::getMoveUpUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_DOWN, PRESSED),
		ActionFactory::getMoveDown()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_DOWN, RELEASED),
		ActionFactory::getMoveDownUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>('W', PRESSED),
		ActionFactory::getBurst()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>('Q', PRESSED),
		ActionFactory::getDashLeft()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>('D', PRESSED),
		ActionFactory::getDashRight()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>('S', PRESSED),
		ActionFactory::getShield()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>('X', PRESSED),
		ActionFactory::getCharge()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>('X', RELEASED),
		ActionFactory::getShoot()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>('C', PRESSED),
		ActionFactory::getSlash()
	);

	// Init directions
	for ( int i = 0; i < 4; ++i )
	{
		_moves[i] = false;
	}
};
Game::~Game( void )
{
	// TODO: Dealloc
};
void Game::load( const string& save )
{
	//_player = s;

	ifstream savegame( save + ".sav", ifstream::in );
	if ( !savegame )
	{
		throw;
	}
	// Memory blocks
	int elementsCount = 0;
	savegame::ElementBlock element;
	savegame::HopeBlock hope;

	// Read player
	savegame >> hope;
	savegame.read((char*)&elementsCount, sizeof(int));

	_player = new Hope(
		structs::Point( hope.x, hope.y, hope.z ),
		structs::Vector3( hope.dx, hope.dy, hope.dz ),
		hope.hp,
		hope.maxHp,
		hope.energy,
		hope.maxEnergy
	);
	_player->setCurrentWeapon( hope.currentWeapon );
	//TODO: Add Weapon
	
	for ( int i = 0; i < elementsCount; ++i )
	{
		// Read other elements
		savegame >> element;

		Element* el;
		
		switch ( element.type )
		{
		case savegame::ElementBlock::ANGEL:
			el = ElementFactory::getAngel(
				structs::Point( element.x, element.y, element.z ),
				structs::Vector3( element.dx, element.dy, element.dz ),
				element.hp,
				element.hpmax
			);
			break;
		/*case savegame::ElementBlock::ARCHANGEL:
			el = ElementFactory::getArchangel();
			break;
		case savegame::ElementBlock::RULER:
			el = ElementFactory::getRuler();
			break;
		case savegame::ElementBlock::AUTHORITY:
			el = ElementFactory::getAuthority();
			break;
		case savegame::ElementBlock::VIRTUE:
			el = ElementFactory::getAngel();
			break;
		case savegame::ElementBlock::DOMINION:
			el = ElementFactory::getDominion();
			break;
		case savegame::ElementBlock::THRONE:
			el = ElementFactory::getThrone();
			break;
		case savegame::ElementBlock::CHERUB:
			el = ElementFactory::getCherub();
			break;
		case savegame::ElementBlock::SERAPH:
			el = ElementFactory::getSeraph();
			break;*/
		}

		_elements.push_back( el );
	}
	savegame.close();
};
void Game::create()
{
	load(
		"save"
	);
};
void Game::reset( void )
{
	// Reset
};
void Game::run( void )
{
	LARGE_INTEGER tick;
	LARGE_INTEGER overhead;
	LARGE_INTEGER freq;
	LONGLONG elapsedTime;

	QueryPerformanceCounter( &tick );
	QueryPerformanceCounter( &overhead );
	QueryPerformanceFrequency( &freq );

	_lastTick.QuadPart = overhead.QuadPart;
	overhead.QuadPart -= tick.QuadPart;

	while ( true )
	{
		QueryPerformanceCounter( &tick );
		elapsedTime = (tick.QuadPart - _lastTick.QuadPart)/freq.QuadPart;
		
		_input( elapsedTime );
		_update( elapsedTime );
		_draw( elapsedTime );

		_lastTick.QuadPart = tick.QuadPart;
	}
};
void Game::_input( LONGLONG elapsedTime )
{
	if ( _moves[UP] )
	{
		_getPlayer()->move( structs::Vector3(0.f, 0.f, .005f) );
	}
	if ( _moves[DOWN] )
	{
		_getPlayer()->move( structs::Vector3(0.f, 0.f, -.005f) );
	}
	if ( _moves[LEFT] )
	{
		_getPlayer()->move( structs::Vector3(-.005f, 0.f, 0.f) );
	}
	if ( _moves[RIGHT] )
	{
		_getPlayer()->move( structs::Vector3(.005f, 0.f, 0.f) );
	}

	while ( !_actionsQueue.empty() )
	{
		Action a = _actionsQueue.front();
		_actionsQueue.pop();
		switch ( a )
		{
		case DASH_LEFT:
			_getPlayer()->dash( structs::Vector3(-1.f, 0.f, 0.f) );
			break;
		case DASH_RIGHT:
			_getPlayer()->dash( structs::Vector3(1.f, 0.f, 0.f) );
			break;
		case CHARGE:
			_getPlayer()->charge();
			break;
		case SHOOT:
			_bullets.splice(
				_bullets.end(),
				_getPlayer()->shoot()
			);
			break;
		case BURST:
			_bullets.splice(
				_bullets.end(),
				_getPlayer()->burst()
			);
			break;
		case SLASH:
			_getPlayer()->slash();
			break;
		case SHIELD:
			_getPlayer()->shield( elapsedTime );
			break;
		}
	}
};
void Game::_update( LONGLONG elapsedTime )
{
	// Update scrolling
	_getPlayer()->update( elapsedTime );
	_updateElements( elapsedTime, _elements );
	
	_bulletsMutex.lock();
	_updateElements( elapsedTime, _bullets );

	// Resolve collisions
	list<Element*> player;
	player.push_back( _getPlayer() );
	_resolveCollisions( player, _bullets );
	_resolveCollisions( _elements, _bullets );
	_bulletsMutex.unlock();
	_resolveCollisions( player, _elements );
};
void Game::_resolveCollisions(
	list<Element*>& hittables,
	list<Element*>& hitters
)
{
	for ( list<Element*>::iterator hitter = hitters.begin();
		hitter != hitters.end();
		++hitter )
	{
		for ( list<Element*>::iterator hittable = hittables.begin();
			hittable != hittables.end();
			++hittable )
		{
			if ( (*hitter)->hit(**hittable) )
			{
				((Ship*)*hittable)->damage( 1 );
				if ( _bulletReflected )
				{

				}
				break;
			}
		}
	}
};
void Game::_updateElements( LONGLONG elapsedTime, list<Element*>& elements )
{
	for ( list<Element*>::iterator it = elements.begin();
		it != elements.end();
		++it )
	{
		(*it)->update( elapsedTime );
	}
};
void Game::_draw( LONGLONG elapsedTime )
{
	structs::Point p = _getPlayer()->getPosition();
	Service::getGraphics()->setCamera(
		0.f, -5.f + p.y/2, 0.f,
		0.f, 0.f + p.y/2, 0.f,
		0.f, 0.f, 1.f
	);
	Service::getGraphics()->setPerspective( DirectX::XM_PIDIV4, 16.f/9.f, 3.f, 1000.f );

	Service::getGraphics()->begin();
	_drawMeshes( _getPlayer()->getMesh() );
	_drawElements( _elements );

	_bulletsMutex.lock();
	_drawElements( _bullets );
	_bulletsMutex.unlock();

	Service::getGraphics()->end();

	// Draw game
	// Draw HUD
};
void Game::_drawElements( const list<Element*>& elements )
{
	for ( list<Element*>::const_iterator it = elements.begin();
		it != elements.end();
		++it )
	{
		_drawMeshes( (*it)->getMesh() );
	}
};
void Game::_drawMeshes( const vector<Mesh*>& meshes )
{
	for ( vector<Mesh*>::const_iterator it = meshes.begin();
		it != meshes.end();
		++it )
	{
		Service::getGraphics()->draw(
			&(*it)->getVertexes()[0],
			(*it)->getVertexes().size(),
			(*it)->getTexture()
		);
	}
};
void Game::update( const HopeAction& action, void* params )
{
	//throw;
};
void Game::update( const BulletAction& action, void* params )
{
	switch (action)
	{
	case BULLET_REFLECTED:
		_bulletReflected = true;
		break;
	case BULLET_DEATH:
		_bulletsMutex.lock();
		Element* el = (Element*)params;
		//delete params;
		_bullets.remove( (Element*)params );
		_bulletsMutex.unlock();
		break;
	}
};
void Game::action( const Action& action )
{
	_actionsQueue.push( action );
};
void Game::MoveLeft( void )
{
	_moves[LEFT] = true;
};
void Game::MoveRight( void )
{
	_moves[RIGHT] = true;
};
void Game::MoveUp( void )
{
	_moves[UP] = true;
};
void Game::MoveDown( void )
{
	_moves[DOWN] = true;
};
void Game::SwapForm( void )
{
};
Hope* Game::_getPlayer( void )
{
	return _player;
};
void shield::Game::MoveUpUp( void )
{
	_moves[UP] = false;
};
void shield::Game::MoveDownUp( void )
{
	_moves[DOWN] = false;
};
void shield::Game::MoveRightUp( void )
{
	_moves[RIGHT] = false;
};
void shield::Game::MoveLeftUp( void )
{
	_moves[LEFT] = false;
};
