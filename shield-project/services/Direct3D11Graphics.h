#ifndef _DIRECT3D11GRAPHICS_H_
#define _DIRECT3D11GRAPHICS_H_

#include <d3d11_1.h>
#include "IGraphics.h"

namespace shield {
namespace services {
	class Direct3D11Graphics : public IGraphics
	{
	public:
		enum {
			DEFAULT_ADAPTER	= 0,
			WIDTH			= 1920,
			HEIGHT			= 1080,
			FRAMERATE_NUM	= 60,
			FRAMERATE_DEN	= 1
		};
		Direct3D11Graphics( HWND );

	private:
		HWND _hwnd;
		IDXGIFactory* _factory;
		ID3D11Device* _device;
		ID3D11DeviceContext* _deviceContext;
		IDXGISwapChain* _swapChain;
		IDXGIFactory* _getFactory();
		void _initDevice();
		void _initSwapChain();
	};
};
};

#endif
