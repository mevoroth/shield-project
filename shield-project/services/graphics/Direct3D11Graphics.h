#ifndef _DIRECT3D11GRAPHICS_H_
#define _DIRECT3D11GRAPHICS_H_

#include <map>
#include <d3d11_1.h>
#include "IGraphics.h"
#include "..\..\Settings.h"

#include "..\..\libs\FW1FontWrapper.h"

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
			WIDTH			= settings::system::WIDTH,
			HEIGHT			= settings::system::HEIGHT,
			FRAMERATE_NUM	= 60,
			FRAMERATE_DEN	= 1
		};
		Direct3D11Graphics( HWND );
		~Direct3D11Graphics( void );
		void begin( void );
		void end( void );
		void draw( const Vertex[], int, const wchar_t*, void*, void*, void* );
		void setCamera(
			float, float, float,
			float, float, float,
			float, float, float
		);
		void setPerspective( float, float, float, float );
		/**
		 * Crée un buffer constant
		 * @param[in] Shader
		 * @param[in] Slot
		 * @param[in] Size of buffer
		 */
		void createConstantBuffer( UINT16, UINT16, int );
		/**
		 * Update un buffer constant
		 * @param[in] Shader
		 * @param[in] Slot
		 * @param[in] Value
		 */
		void updateConstantBuffer( UINT16, UINT16, void* );
		void setShaderResource( UINT16, UINT16, ID3D11ShaderResourceView* );
		void setSamplerState( UINT16, UINT16, const D3D11_SAMPLER_DESC& );
		/**
		 * @param[in] Chemin texture
		 * @param[out] Ressource
		 */
		void loadTexture(
			const wchar_t*,
			ID3D11ShaderResourceView*&
		);
		template<class Shader> void loadShader( UINT16, ID3D10Blob* );
		template<class Shader> void useShader( UINT16 );
		void updateMatrix();
		void write( const std::string& );

	private:
		HWND _window;
		IDXGIFactory* _factory;
		ID3D11Device* _device;
		ID3D11DeviceContext* _deviceContext;
		IDXGISwapChain* _swapChain;
		ID3D11RenderTargetView* _renderTarget;
		/**
		 * Bibliothèques de shaders
		 */
		map<UINT16, ID3D11DeviceChild*> _shaders;
		/**
		 * Buffers constants de shaders
		 */
		map<UINT16, map<UINT16, ID3D11Buffer*>> _constantBuffers;
		/**
		 * Ressources shaders
		 */
		map<UINT16, map<UINT16, ID3D11ShaderResourceView*>> _shaderResources;
		/**
		 * Options de shaders
		 */
		map<UINT16, map<UINT16, ID3D11SamplerState*>> _samplerStates;
		/**
		 * Bibliothèque de textures
		 */
		map<const wchar_t*, ID3D11ShaderResourceView*> _textures;
		ID3D11InputLayout* _inputLayout;
		ID3D11Buffer* _matrixBuffer;
		ID3D11DepthStencilView* _depthStencilView;
		IFW1Factory* _fw1Factory;
		IFW1FontWrapper* _fontWrapper;
		DirectX::XMMATRIX _worldMatrix;
		DirectX::XMMATRIX _viewMatrix;
		DirectX::XMMATRIX _projectionMatrix;

		UINT16 _currentVertex;
		UINT16 _currentGeometry;

		void _createVertexBuffer( const Vertex[], int, ID3D11Buffer*& );
		//void _createMatrixBuffer(  );
		IDXGIFactory* _getFactory( void );
		void _initDeviceAndSwapChain( void );
		void _initRenderTarget( void );
		void _initViewport( void );
		void _setBlendState( void );
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
			const map<UINT16, ID3D11Buffer*>&,
			const map<UINT16, ID3D11ShaderResourceView*>&,
			const map<UINT16, ID3D11SamplerState*>&
		);
		/**
		 * Use hull shader
		 */
		void _useShader(
			ID3D11HullShader*,
			const map<UINT16, ID3D11Buffer*>&,
			const map<UINT16, ID3D11ShaderResourceView*>&,
			const map<UINT16, ID3D11SamplerState*>&
		);
		/**
		 * Use domain shader
		 */
		void _useShader(
			ID3D11DomainShader*,
			const map<UINT16, ID3D11Buffer*>&,
			const map<UINT16, ID3D11ShaderResourceView*>&,
			const map<UINT16, ID3D11SamplerState*>&
		);
		/**
		 * Use geometry shader
		 */
		void _useShader(
			ID3D11GeometryShader*,
			const map<UINT16, ID3D11Buffer*>&,
			const map<UINT16, ID3D11ShaderResourceView*>&,
			const map<UINT16, ID3D11SamplerState*>&
		);
		/**
		 * Use pixel shader
		 */
		void _useShader(
			ID3D11PixelShader*,
			const map<UINT16, ID3D11Buffer*>&,
			const map<UINT16, ID3D11ShaderResourceView*>&,
			const map<UINT16, ID3D11SamplerState*>&
		);
		void _createInputLayout( ID3D10Blob* );
	};
};
};

#endif
