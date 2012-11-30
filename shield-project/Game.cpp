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
	/*Service::getGraphics()->setCamera(
		0.f, 3.f, -6.f,
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f
	);*/
	Service::getGraphics()->setPerspective( DirectX::XM_PIDIV4, 16.f/9.f, .1f, 10.f );
	/*Service::getGraphics()->setPerspective( DirectX::XM_PIDIV4, 16.f/9.f, .1f, 10.0f );*/

	Vertex buffer[24];
	//[0] = {pos={x=1.00000000 y=-0.736452997 z=0.413895011 } }
	//[1] = {pos={x=-1.00000000 y=-0.736452997 z=0.413895011 } }
	//[2] = {pos={x=1.00000000 y=1.26354694 z=0.413895011 } }
	//[3] = {pos={x=-1.00000000 y=1.26354694 z=0.413895011 } }
	buffer[0].pos = DirectX::XMFLOAT3( -1.0f, 1.0f, -1.0f );
	buffer[1].pos = DirectX::XMFLOAT3( 1.0f, 1.0f, -1.0f );
	buffer[2].pos = DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f );
	buffer[3].pos = DirectX::XMFLOAT3( -1.0f, 1.0f, 1.0f );

	buffer[4].pos = DirectX::XMFLOAT3( -1.0f, -1.0f, -1.0f );
	buffer[5].pos = DirectX::XMFLOAT3( 1.0f, -1.0f, -1.0f );
	buffer[6].pos = DirectX::XMFLOAT3( 1.0f, -1.0f, 1.0f );
	buffer[7].pos = DirectX::XMFLOAT3( -1.0f, -1.0f, 1.0f );

	buffer[8].pos = DirectX::XMFLOAT3( -1.0f, -1.0f, 1.0f );
	buffer[9].pos = DirectX::XMFLOAT3( -1.0f, -1.0f, -1.0f );
	buffer[10].pos = DirectX::XMFLOAT3( -1.0f, 1.0f, -1.0f );
	buffer[11].pos = DirectX::XMFLOAT3( -1.0f, 1.0f, 1.0f );

	buffer[12].pos = DirectX::XMFLOAT3( 1.0f, -1.0f, 1.0f );
	buffer[13].pos = DirectX::XMFLOAT3( 1.0f, -1.0f, -1.0f );
	buffer[14].pos = DirectX::XMFLOAT3( 1.0f, 1.0f, -1.0f );
	buffer[15].pos = DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f );

	buffer[16].pos = DirectX::XMFLOAT3( -1.0f, -1.0f, -1.0f );
	buffer[17].pos = DirectX::XMFLOAT3( 1.0f, -1.0f, -1.0f );
	buffer[18].pos = DirectX::XMFLOAT3( 1.0f, 1.0f, -1.0f );
	buffer[19].pos = DirectX::XMFLOAT3( -1.0f, 1.0f, -1.0f );

	buffer[20].pos = DirectX::XMFLOAT3( -1.0f, -1.0f, 1.0f );
	buffer[21].pos = DirectX::XMFLOAT3( 1.0f, -1.0f, 1.0f );
	buffer[22].pos = DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f );
	buffer[23].pos = DirectX::XMFLOAT3( -1.0f, 1.0f, 1.0f );
	/*buffer[0].pos = DirectX::XMFLOAT3(1.f,-0.736452997f,0.413895011f);
	buffer[1].pos = DirectX::XMFLOAT3(-1.f,-0.736452997,0.413895011f);
	buffer[2].pos = DirectX::XMFLOAT3(1.f,1.26354694f,0.413895011f);
	buffer[3].pos = DirectX::XMFLOAT3(-1.f,1.26354694f,0.413895011);*/

	int indices[] = {
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

	const Mesh* mesh = _player->getMesh();
	Service::getGraphics()->draw(
		&mesh->getVertexes()[0],
		mesh->getVertexes().size(),
		&mesh->getIndices()[0],
		mesh->getIndices().size()
	);
	/*Service::getGraphics()->draw(
		buffer,
		24,
		indices,
		36
	);*/
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
