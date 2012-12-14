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
		void begin( void );
		void end( void );
		void draw( const Vertex[], int, const std::string& );
		void setCamera(
			float, float, float,
			float, float, float,
			float, float, float
		);
		void setPerspective( float, float, float, float );
		/**
		 * Create constant buffer
		 * @param[in] Shader
		 * @param[in] Slot
		 * @param[in] Size of buffer
		 */
		void createConstantBuffer( UINT16, UINT16, int );
		/**
		 * Update constant buffer value
		 * @param[in] Shader
		 * @param[in] Slot
		 * @param[in] Value
		 */
		void updateConstantBuffer( UINT16, UINT16, void* );
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
		map<UINT16, ID3D11DeviceChild*> _shaders;
		/**
		 * Buffers constants de shaders
		 */
		map<UINT16, map<UINT16, ID3D11Buffer*>> _constantsBuffers;
		ID3D11InputLayout* _inputLayout;
		ID3D11Buffer* _matrixBuffer;
		DirectX::XMMATRIX _worldMatrix;
		DirectX::XMMATRIX _viewMatrix;
		DirectX::XMMATRIX _projectionMatrix;

		void _createVertexBuffer( const Vertex[], int, ID3D11Buffer*& );
		//void _createMatrixBuffer(  );
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
		void _useShader(
			ID3D11VertexShader*,
			const map<UINT16, ID3D11Buffer*>&
		);
		/**
		 * Use hull shader
		 */
		void _useShader(
			ID3D11HullShader*,
			const map<UINT16, ID3D11Buffer*>&
		);
		/**
		 * Use domain shader
		 */
		void _useShader(
			ID3D11DomainShader*,
			const map<UINT16, ID3D11Buffer*>&
		);
		/**
		 * Use geometry shader
		 */
		void _useShader(
			ID3D11GeometryShader*,
			const map<UINT16, ID3D11Buffer*>&
		);
		/**
		 * Use pixel shader
		 */
		void _useShader(
			ID3D11PixelShader*,
			const map<UINT16, ID3D11Buffer*>&
		);
		void _createInputLayout( ID3D10Blob* );
	};
};
};

#endif
