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

#include "services\graphics\Direct3D11Graphics.h"

using namespace std;
using namespace shield;
using namespace shield::services;
using namespace shield::savegame;
using namespace DirectX;

Game::Game( void )
	: _bulletReflected( false ),
	_end( false )
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
		ActionFactory::getStopLeft()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_RIGHT, PRESSED),
		ActionFactory::getMoveRight()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_RIGHT, RELEASED),
		ActionFactory::getStopRight()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_UP, PRESSED),
		ActionFactory::getMoveUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_UP, RELEASED),
		ActionFactory::getStopUp()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_DOWN, PRESSED),
		ActionFactory::getMoveDown()
	);
	Service::getControls()->bind(
		new pair<WPARAM, ControlsState>(VK_DOWN, RELEASED),
		ActionFactory::getStopDown()
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
void Game::load( const string& save, const string& map )
{
	//_player = s;

	ifstream savegame( save + ".sav", ifstream::in );
	ifstream mapfile( map + ".map", ifstream::in );

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
	savegame.close();
	
	hope.x = 2.f;
	hope.y = 2.f;
	hope.z = 2.f;
	
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
	
	mapfile.read((char*)&elementsCount, sizeof(int));

	for ( int i = 0; i < elementsCount; ++i )
	{
		// Read other elements
		mapfile >> element;

		Element* el;
		
		switch ( element.type )
		{
		case savegame::ElementBlock::ANGEL:
			el = ElementFactory::getAngel(
				structs::Point( element.x, element.y, element.z ),
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

	//mapfile >> _triggerEnd;
	_triggerEnd = 20.f;

	mapfile.close();
};
void Game::create()
{
	load(
		"save",
		"map"
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

	while ( !_end )
	{
		QueryPerformanceCounter( &tick );
		elapsedTime = (tick.QuadPart - _lastTick.QuadPart)/freq.QuadPart;
		
		_input( elapsedTime );
		_update( elapsedTime );
		_draw( elapsedTime );

		_lastTick.QuadPart = tick.QuadPart;
	}
};
bool Game::end( void )
{
	_end = (_getPlayer()->getPosition().y > _triggerEnd);
	return _end;
};
void Game::_input( LONGLONG elapsedTime )
{
	_getPlayer()->move(
		structs::Vector3(
			(_moves[LEFT] ? -.1f : 0.f) + (_moves[RIGHT] ? .1f : 0.f),
			0.f,
			(_moves[UP] ? .1f : 0.f) + (_moves[DOWN] ? -.1f : 0.f)
		)
	);

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
	list<Element*> player;
	player.push_back( _getPlayer() );

	// Update scrolling
	_getPlayer()->update( elapsedTime );
	_updateElements( elapsedTime, _elements );
	
	_bulletsMutex.lock();
	_updateElements( elapsedTime, _bullets );

	// Resolve collisions
	_resolveCollisions( player, _bullets );
	_resolveCollisions( _elements, _bullets );
	_bulletsMutex.unlock();
	_resolveCollisions( player, _elements );

	// Shooting
	for ( list<Element*>::iterator it = _elements.begin();
		it != _elements.end();
		++it )
	{
		std::list<Element*> els = ((Ship*)*it)->shoot();
		_bulletsMutex.lock();
		_bullets.splice(
			_bullets.end(),
			els
		);
		_bulletsMutex.unlock();
	}

	// Clean
	_elements.remove_if( death_elements );
	_bulletsMutex.lock();
	_bullets.remove_if( death_elements );
	_bulletsMutex.unlock();
};
bool shield::death_elements( const Element* e )
{
	return e->isDead();
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
					// Bullet reflected
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
	float camera = 4.5f*settings::system::WIDTH/(tan(XM_PI/36.f)*settings::system::HEIGHT*2.f);
	Service::getGraphics()->setCamera(
		2.5f, -camera + p.y, 2.5f,
		2.5f, 0.f + p.y, 2.5f,
		0.f, 0.f, 1.f
	);

	Service::getGraphics()->setPerspective(
		XM_PI/18.f,
		settings::system::RATIO,
		0.01f,
		5000.f
	);

	Service::getGraphics()->begin();
	
	XMFLOAT3 null_v( 0.f, 0.f, 0.f );

	XMFLOAT3 cube[8];
	cube[0] = XMFLOAT3(-10.f, -10.f + p.y, 10.f);
	cube[1] = XMFLOAT3(10.f, -10.f + p.y, 10.f);
	cube[2] = XMFLOAT3(10.f, -10.f + p.y, -10.f);
	cube[3] = XMFLOAT3(-10.f, -10.f + p.y, -10.f);
	cube[4] = XMFLOAT3(-10.f, 10.f + p.y, 10.f);
	cube[5] = XMFLOAT3(10.f, 10.f + p.y, 10.f);
	cube[6] = XMFLOAT3(10.f, 10.f + p.y, -10.f);
	cube[7] = XMFLOAT3(-10.f, 10.f + p.y, -10.f);

	XMFLOAT2 square[4];
	square[0] = XMFLOAT2( 0.f, 0.f );
	square[1] = XMFLOAT2( 4.f, 0.f );
	square[2] = XMFLOAT2( 4.f, 4.f );
	square[3] = XMFLOAT2( 0.f, 4.f );

	// Draw stars
	structs::Vertex space[30] = {
		/*{ cube[0], null_v, square[0] },
		{ cube[1], null_v, square[1] },
		{ cube[2], null_v, square[2] },
		{ cube[0], null_v, square[0] },
		{ cube[1], null_v, square[1] },
		{ cube[3], null_v, square[3] },*/
		
		{ cube[5], null_v, square[0] },
		{ cube[1], null_v, square[1] },
		{ cube[2], null_v, square[2] },
		{ cube[5], null_v, square[0] },
		{ cube[1], null_v, square[1] },
		{ cube[6], null_v, square[3] },
		
		{ cube[4], null_v, square[0] },
		{ cube[5], null_v, square[1] },
		{ cube[6], null_v, square[2] },
		{ cube[4], null_v, square[0] },
		{ cube[6], null_v, square[1] },
		{ cube[7], null_v, square[3] },
		
		{ cube[0], null_v, square[0] },
		{ cube[4], null_v, square[1] },
		{ cube[7], null_v, square[2] },
		{ cube[0], null_v, square[0] },
		{ cube[7], null_v, square[1] },
		{ cube[3], null_v, square[3] },
		
		{ cube[0], null_v, square[0] },
		{ cube[1], null_v, square[1] },
		{ cube[5], null_v, square[2] },
		{ cube[0], null_v, square[0] },
		{ cube[5], null_v, square[1] },
		{ cube[4], null_v, square[3] },
		
		{ cube[7], null_v, square[0] },
		{ cube[6], null_v, square[1] },
		{ cube[2], null_v, square[2] },
		{ cube[7], null_v, square[0] },
		{ cube[2], null_v, square[1] },
		{ cube[3], null_v, square[3] }
	};
	Service::getGraphics()->draw(
		space,
		30,
		L"stars",
		(void*)0,
		(void*)-1,
		(void*)4
	);

	_drawMeshes( *_getPlayer()->getMesh() );
	_drawElements( _elements );

	_bulletsMutex.lock();
	_drawElements( _bullets );
	_bulletsMutex.unlock();

	// Draw HUD
	_drawHud();

	Service::getGraphics()->end();
};
void Game::_drawElements( const list<Element*>& elements )
{
	Point player = _getPlayer()->getPosition();
	for ( list<Element*>::const_iterator it = elements.begin();
		it != elements.end();
		++it )
	{
		if ( (*it)->isVisible(player) )
		{
			_drawMeshes( *(*it)->getMesh() );
		}
	}
};
void Game::_drawMeshes( const vector<Mesh*>& meshes )
{
	Service::getGraphics()->updateMatrix();
	for ( vector<Mesh*>::const_iterator it = meshes.begin();
		it != meshes.end();
		++it )
	{
		std::vector<structs::Vertex>* vertexes = (*it)->getVertexes();
		Service::getGraphics()->draw(
			&(*vertexes)[0],
			vertexes->size(),
			(*it)->getTexture(),
			(void*)0,
			(void*)2,
			(void*)1
		);
	}
};
void Game::_drawHud( void )
{
	// Draw HUD
	structs::Vertex hud[6];
	hud[0].pos = XMFLOAT3( -1.f, 1.f, 0.01f );
	hud[0].tex = XMFLOAT2( 0.f, 0.f );
	hud[1].pos = XMFLOAT3( 1.f, 1.f, 0.01f );
	hud[1].tex = XMFLOAT2( 1.f, 0.f );
	hud[2].pos = XMFLOAT3( -1.f, -1.f, 0.01f );
	hud[2].tex = XMFLOAT2( 0.f, 1.f );
	hud[3].pos = XMFLOAT3( 1.f, 1.f, 0.01f );
	hud[3].tex = XMFLOAT2( 1.f, 0.f );
	hud[4].pos = XMFLOAT3( 1.f, -1.f, 0.01f );
	hud[4].tex = XMFLOAT2( 1.f, 1.f );
	hud[5].pos = XMFLOAT3( -1.f, -1.f, 0.01f );
	hud[5].tex = XMFLOAT2( 0.f, 1.f );
	
	Service::getGraphics()->draw(
		hud,
		6,
		L"hud",
		(void*)3,
		(void*)-1,
		(void*)4
	);

	// Draw Shield
	float px = 325.f/(settings::system::WIDTH*6.f);
	float mx = -px;
	float py = 425.f/(settings::system::HEIGHT*6.f);
	float my = -py;
	px -= 0.70f;
	mx -= 0.70f;
	py -= 0.70f;
	my -= 0.70f;
	structs::Vertex shield[6];
	shield[0].pos = XMFLOAT3( mx, py, 0.f );
	shield[0].tex = XMFLOAT2( 0.f, 0.f );
	shield[1].pos = XMFLOAT3( px, py, 0.f );
	shield[1].tex = XMFLOAT2( 1.f, 0.f );
	shield[2].pos = XMFLOAT3( mx, my, 0.f );
	shield[2].tex = XMFLOAT2( 0.f, 1.f );
	shield[3].pos = XMFLOAT3( px, py, 0.f );
	shield[3].tex = XMFLOAT2( 1.f, 0.f );
	shield[4].pos = XMFLOAT3( px, my, 0.f );
	shield[4].tex = XMFLOAT2( 1.f, 1.f );
	shield[5].pos = XMFLOAT3( mx, my, 0.f );
	shield[5].tex = XMFLOAT2( 0.f, 1.f );

	Service::getGraphics()->draw(
		shield,
		6,
		L"Logo_Shield_Disabled",
		(void*)3,
		(void*)-1,
		(void*)4
	);

	// Draw Charge
	px += 500.f/(settings::system::WIDTH*3.f);
	mx += 500.f/(settings::system::WIDTH*3.f);
	structs::Vertex charge[6];
	charge[0].pos = XMFLOAT3( mx, py, 0.f );
	charge[0].tex = XMFLOAT2( 0.f, 0.f );
	charge[1].pos = XMFLOAT3( px, py, 0.f );
	charge[1].tex = XMFLOAT2( 1.f, 0.f );
	charge[2].pos = XMFLOAT3( mx, my, 0.f );
	charge[2].tex = XMFLOAT2( 0.f, 1.f );
	charge[3].pos = XMFLOAT3( px, py, 0.f );
	charge[3].tex = XMFLOAT2( 1.f, 0.f );
	charge[4].pos = XMFLOAT3( px, my, 0.f );
	charge[4].tex = XMFLOAT2( 1.f, 1.f );
	charge[5].pos = XMFLOAT3( mx, my, 0.f );
	charge[5].tex = XMFLOAT2( 0.f, 1.f );

	Service::getGraphics()->draw(
		charge,
		6,
		L"Logo_Charge_Disabled",
		(void*)3,
		(void*)-1,
		(void*)4
	);

	//((Direct3D11Graphics*)Service::getGraphics())->write( "trololo" );
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
	/*case BULLET_DEATH:
		Element* el = (Element*)params;
		_bulletsMutex.lock();
		//delete params;
		_bullets.remove( (Element*)params );
		_bulletsMutex.unlock();
		break;*/
	}
};
void Game::action( const Action& action )
{
	_actionsQueue.push( action );
};
void Game::move( const Direction& dir, bool moving )
{
	_moves[dir] = moving;
};
void Game::SwapForm( void )
{
};
Hope* Game::_getPlayer( void )
{
	return _player;
};
