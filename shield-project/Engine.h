#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <Windows.h>
#include "Game.h"

namespace shield
{
	class Engine
	{
	public:
		Engine( HINSTANCE, int );
		void run( void );
		void close( void );

	private:
		HWND _window;
		WNDCLASSEX* _windowClass;
		HINSTANCE _hInst;
		int _nCmdShow;
		void _registerClass();
		void _createWindow();
	};
	LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
}

#endif
