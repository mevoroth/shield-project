#include "Direct3D11Graphics.h"

#include <d3d11.h>
#include <dxgi.h>

using namespace shield;

services::Direct3D11Graphics::Direct3D11Graphics( HWND hwnd )
	: _hwnd( hwnd ),
	_factory( 0 ),
	_device( 0 ),
	_deviceContext( 0 ),
	_swapChain( 0 )
{
	_initDevice();
	_initSwapChain();
};
void services::Direct3D11Graphics::_initDevice()
{
	D3D_FEATURE_LEVEL features[] = {
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL feature_returned;

	HRESULT hr = D3D11CreateDevice(
		0,					// Adapter (Carte graphique)
		D3D_DRIVER_TYPE_HARDWARE,	// Driver
		0,							// Software rasterizer
		0,							// Flags
		features,                   // Liste des versions
		ARRAYSIZE(features),		// Taille de la liste des versions
		D3D11_SDK_VERSION,			// SDK
		&_device,					// Device
		&feature_returned,			// Version choisie
		&_deviceContext				// Device Context
	);

	if ( hr != S_OK )
	{
		throw "Impossible de créer le device Direct3D";
	}
};
void services::Direct3D11Graphics::_initSwapChain()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	swapChainDesc.BufferDesc.Width						= WIDTH;
	swapChainDesc.BufferDesc.Height						= HEIGHT;
	swapChainDesc.BufferDesc.RefreshRate.Numerator		= FRAMERATE_NUM;
	swapChainDesc.BufferDesc.RefreshRate.Denominator	= FRAMERATE_DEN;
	swapChainDesc.BufferDesc.ScanlineOrdering			=
		DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	swapChainDesc.BufferDesc.Format						= DXGI_FORMAT_R8G8B8A8_UINT;
	swapChainDesc.BufferDesc.Scaling					= DXGI_MODE_SCALING_CENTERED;

	swapChainDesc.SampleDesc.Count		= 1;
	swapChainDesc.SampleDesc.Quality	= 0;

	swapChainDesc.BufferUsage	= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount	= 0;
	swapChainDesc.OutputWindow	= _hwnd;
	swapChainDesc.Windowed		= false;
	swapChainDesc.SwapEffect	= DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags			= 0;

	HRESULT hr = _getFactory()->CreateSwapChain(
		_device,
		&swapChainDesc,
		&_swapChain
	);

	/* if ( !hr )
	{
	} */
};
IDXGIFactory* services::Direct3D11Graphics::_getFactory()
{
	if ( _factory == 0 )
	{
		CreateDXGIFactory1(
			__uuidof(IDXGIFactory),
			(void**)(&_factory)
		);
	}
	return _factory;
};