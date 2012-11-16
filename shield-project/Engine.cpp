#include "Engine.h"
#include "Service.h"

#include "services\controls\KeyboardControls.h"
#include "services\graphics\Direct3D11Graphics.h"
#include "services\sound\NullSound.h"

#include "Game.h"
#include "Settings.h"
using namespace shield;

Engine::Engine( HINSTANCE hInst, int nCmdShow )
	: _window( 0 ),
	_windowClass( 0 ),
	_hInst( hInst ),
	_nCmdShow( nCmdShow )
{
	//try
	//{
		_registerClass();
		_createWindow();
	//}
	//catch (char* err)
	//{
	//}
	Service::setControls( new services::KeyboardControls() );
	Service::setGraphics( new services::Direct3D11Graphics(_window) );
	Service::setSound( new services::NullSound() );
};

void Engine::run()
{
	// Load menu

	// New game
	Game g;
	g.create();
	//g.run();

	MSG msg = {0};
	while ( msg.message != WM_QUIT )
	{
		if ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			g.render();
		}
	}
};
void Engine::_registerClass()
{
	// Setting window class struct
	_windowClass = new WNDCLASSEX;
	_windowClass->cbSize = sizeof( WNDCLASSEX );
	_windowClass->style = CS_HREDRAW | CS_VREDRAW;
	_windowClass->lpfnWndProc = WndProc;
	_windowClass->cbClsExtra = 0;
	_windowClass->cbWndExtra = 0;
	_windowClass->hInstance = _hInst;
	_windowClass->hIcon = 0;
	_windowClass->hCursor = LoadCursor( 0, IDC_ARROW );
	_windowClass->hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	_windowClass->lpszMenuName = 0;
	_windowClass->lpszClassName = "ShieldWindow";
	_windowClass->hIconSm = 0;

	if ( !RegisterClassEx(_windowClass) )
	{
		throw "Can't register ShieldWindow";
	}
};
void Engine::_createWindow()
{
	// Create window
	_window = CreateWindow(
		"ShieldWindow",
		"Shield",
		WS_VISIBLE | WS_MAXIMIZE | WS_EX_TOPMOST,
		0,
		0,
		1920,
		1080,
		0,
		0,
		_hInst,
		0
	);
	if ( !_window )
	{
		throw "Can't create window";
	}
	ShowWindow( _window, _nCmdShow );
};
LRESULT CALLBACK shield::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch( message )
	{
		case WM_KEYDOWN:
			Service::getControls()->keyDown( (void*)&wParam, (void*)&lParam );
			break;

		case WM_KEYUP:
			Service::getControls()->keyUp( (void*)&wParam, (void*)&lParam );
			break;

		case WM_PAINT:
			hdc = BeginPaint( hWnd, &ps );
			EndPaint( hWnd, &ps );
			break;

		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;

		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
};
