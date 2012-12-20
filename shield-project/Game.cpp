#include "Game.h"

#include <map>
#include <fstream>
#include "Service.h"
#include "Settings.h"
#include "game\actions\ActionFactory.h"
#include "services\controls\State.h"
#include "game\elements\ElementFactory.h"
#include "savegame\ElementBlock.h"
#include "savegame\HopeBlock.h"

using namespace std;
using namespace shield;
using namespace shield::services;
using namespace shield::savegame;

Game::Game( void )
{
	ActionFactory::setGame( this );

	// Default binding
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_LEFT, PRESSED),
		ActionFactory::getMoveLeft()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_LEFT, RELEASED),
		ActionFactory::getMoveLeftUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_RIGHT, PRESSED),
		ActionFactory::getMoveRight()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_RIGHT, RELEASED),
		ActionFactory::getMoveRightUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_UP, PRESSED),
		ActionFactory::getMoveUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_UP, RELEASED),
		ActionFactory::getMoveUpUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_DOWN, PRESSED),
		ActionFactory::getMoveDown()
	);
	Service::getControls()->bind(
		new pair<WPARAM, State>(VK_DOWN, RELEASED),
		ActionFactory::getMoveDownUp()
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
	for ( int i = 0; i < 4; ++i )
	{
		_moves[i] = false;
	}
};
Game::~Game( void )
{
	// TODO: Dealloc
};
void Game::load( const std::string& save )
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
	if ( _moves[UP] )
	{
		_getPlayer()->move( structs::Vector3(0.f, 0.f, .001f) );
	}
	if ( _moves[DOWN] )
	{
		_getPlayer()->move( structs::Vector3(0.f, 0.f, -.001f) );
	}
	if ( _moves[LEFT] )
	{
		_getPlayer()->move( structs::Vector3(-.001f, 0.f, 0.f) );
	}
	if ( _moves[RIGHT] )
	{
		_getPlayer()->move( structs::Vector3(.001f, 0.f, 0.f) );
	}
	while ( !_actionsQueue.empty() )
	{
		Action a = _actionsQueue.front();
		_actionsQueue.pop();
		switch ( a )
		{
		/*case MOVE_LEFT:
			_getPlayer()->move( structs::Vector3(-1.f, 0.f, 0.f) );
			break;
		case MOVE_RIGHT:
			_getPlayer()->move( structs::Vector3(1.f, 0.f, 0.f) );
			break;
		case MOVE_UP:
			_getPlayer()->move( structs::Vector3(0.f, 0.f, 1.f) );
			break;
		case MOVE_DOWN:
			_getPlayer()->move( structs::Vector3(0.f, 0.f, -1.f) );
			break;*/
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
		case SLASH:
		case SHIELD:
			break;
		}
	}
};
void Game::_update( ULONGLONG elapsedTime )
{
	_getPlayer()->update( elapsedTime );
	_updateElements( elapsedTime, _elements );
	_updateElements( elapsedTime, _bullets );

	// Faire avancer la camera
	structs::Point p = _getPlayer()->getPosition();

	Service::getGraphics()->setCamera(
		0.f, -5.f + p.y/2, 0.f,
		0.f, 0.f + p.y/2, 0.f,
		0.f, 0.f, 1.f
	);
};
void Game::_updateElements(
	ULONGLONG elapsedTime,
	std::list<Element*>& elements
)
{
	for ( std::list<Element*>::iterator it = elements.begin();
		it != elements.end();
		++it )
	{
		(*it)->update( elapsedTime );
	}
};
void Game::_draw( ULONGLONG elapsedTime )
{
	render();
};
void Game::render()
{
	Service::getGraphics()->setPerspective( DirectX::XM_PIDIV4, 16.f/9.f, .1f, 100.f );
	
	Service::getGraphics()->begin();
	_drawMeshes( _getPlayer()->getMesh() );
	_drawElements( _elements );
	_drawElements( _bullets );
	//((Direct3D11Graphics*)Service::getGraphics())->write("");
	
	Service::getGraphics()->end();

	// Draw game
	// Draw HUD
};
void Game::_drawElements( const std::list<Element*>& elements )
{
	for ( std::list<Element*>::const_iterator it = elements.begin();
		it != elements.end();
		++it )
	{
		_drawMeshes( (*it)->getMesh() );
	}
};
void Game::_drawMeshes( const std::vector<Mesh*>& meshes )
{
	for ( std::vector<Mesh*>::const_iterator it = meshes.begin();
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
void Game::MoveLeft()
{
	_moves[LEFT] = true;
	//_actionsQueue.push( MOVE_LEFT );
};
void Game::MoveRight()
{
	_moves[RIGHT] = true;
	//_actionsQueue.push( MOVE_RIGHT );
};
void Game::MoveUp()
{
	_moves[UP] = true;
	//_actionsQueue.push( MOVE_UP );
};
void Game::MoveDown()
{
	_moves[DOWN] = true;
	//_actionsQueue.push( MOVE_DOWN );
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
void shield::Game::MoveUpUp()
{
	_moves[UP] = false;
};
void shield::Game::MoveDownUp()
{
	_moves[DOWN] = false;
};
void shield::Game::MoveRightUp()
{
	_moves[RIGHT] = false;
};
void shield::Game::MoveLeftUp()
{
	_moves[LEFT] = false;
};
