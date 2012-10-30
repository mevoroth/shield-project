#ifndef _DIRECT3D11GRAPHICS_H_
#define _DIRECT3D11GRAPHICS_H_

#include <map>
#include <d3d11_1.h>
#include "IGraphics.h"

using namespace std;

namespace shield {
namespace services {
	/**
	 * For more information about graphic pipeline, see :
	 * http://msdn.microsoft.com/en-us/library/windows/desktop/bb205123(v=vs.85).aspx
	 */
	class Direct3D11Graphics : public IGraphics
	{
	public:
		enum
		{
			WIDTH			= 1920,
			HEIGHT			= 1080,
			FRAMERATE_NUM	= 60,
			FRAMERATE_DEN	= 1
		};
		Direct3D11Graphics( HWND );
		~Direct3D11Graphics( void );
		template<class Shader> void loadShader( UINT16, ID3D10Blob* );
		template<class Shader> void useShader( UINT16 );

	private:
		HWND _window;
		IDXGIFactory* _factory;
		ID3D11Device* _device;
		ID3D11DeviceContext* _deviceContext;
		IDXGISwapChain* _swapChain;
		ID3D11RenderTargetView* _renderTarget;
		/**
		 * Bibliothèque de shaders
		 */
		map<UINT16, ID3D11DeviceChild*>* _shaders;

		IDXGIFactory* _getFactory( void );
		void _initDeviceAndSwapChain( void );
		void _initRenderTarget( void );
		void _initViewport( void );
		/**
		 * Load vertex shader
		 */
		void _loadShader( ID3D10Blob*, ID3D11VertexShader*& );
		/**
		 * Load hull shader
		 */
		void _loadShader( ID3D10Blob*, ID3D11HullShader*& );
		/**
		 * Load vertex shader
		 */
		void _loadShader( ID3D10Blob*, ID3D11DomainShader*& );
		/**
		 * Load geometry shader
		 */
		void _loadShader( ID3D10Blob*, ID3D11GeometryShader*& );
		/**
		 * Load pixel shader
		 */
		void _loadShader( ID3D10Blob*, ID3D11PixelShader*& );
		/**
		 * Use vertex shader
		 */
		void _useShader( ID3D11VertexShader* );
		/**
		 * Use hull shader
		 */
		void _useShader( ID3D11HullShader* );
		/**
		 * Use domain shader
		 */
		void _useShader( ID3D11DomainShader* );
		/**
		 * Use geometry shader
		 */
		void _useShader( ID3D11GeometryShader* );
		/**
		 * Use pixel shader
		 */
		void _useShader( ID3D11PixelShader* );
	};
};
};

#endif
