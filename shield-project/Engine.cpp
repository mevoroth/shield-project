#include "Engine.h"
#include "Service.h"

#include "services\NullControls.h"
#include "services\NullGraphics.h"
#include "services\NullSound.h"

#include "Game.h"
#include "Settings.h"
#include <fstream>
using namespace shield;

Engine::Engine( HINSTANCE hInst, int nCmdShow )
	: _windowClass( 0 ),
	_hInst( hInst ),
	_nCmdShow( nCmdShow )
{
	try
	{
		_registerClass();
		_createWindow();
	}
	catch (char* err)
	{
		std::ofstream fichier("output");
		fichier << err << std::endl;
	}
	//Service::setControls( new services::KeyboardControls( hInst ) );
	Service::setGraphics( new services::NullGraphics() );
	Service::setSound( new services::NullSound() );
};

void Engine::run()
{
	// Load menu

	// New game
	Game g;
	g.create();
	g.run();
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
	HWND window = CreateWindow(
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
	if ( !window )
	{
		DWORD w = GetLastError();
		throw "Can't create window";
	}
	ShowWindow( window, _nCmdShow );
};
LRESULT CALLBACK shield::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch( message )
	{
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
