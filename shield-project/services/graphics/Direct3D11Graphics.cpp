#include "Direct3D11Graphics.h"

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "WVPMatrix.h"

using namespace shield;

services::Direct3D11Graphics::Direct3D11Graphics( HWND window )
	: _window( window ),
	_factory( 0 ),
	_device( 0 ),
	_deviceContext( 0 ),
	_swapChain( 0 ),
	_renderTarget( 0 )
{
	_initDeviceAndSwapChain();
	_initRenderTarget();
	_initViewport();
	// TODO: REMOVE SHADERS
	ID3D10Blob* vertexShader = 0;
	ID3D10Blob* pixelShader = 0;
	ID3D10Blob* errors = 0;
	HRESULT hr = D3DCompileFromFile( L"testvs.hlsl", 0, 0, "main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG, 0, &vertexShader, &errors );
	if ( FAILED(hr) )
	{
		char* str = (char*)errors->GetBufferPointer();
		throw "Erreur";
	}
	loadShader<ID3D11VertexShader>(0, vertexShader);
	hr = D3DCompileFromFile( L"testps.hlsl", 0, 0, "main", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG, 0, &pixelShader, &errors );
	if ( FAILED(hr) )
	{
		char* str = (char*)errors->GetBufferPointer();
		throw "Erreur";
	}
	loadShader<ID3D11PixelShader>(1, pixelShader);
	useShader<ID3D11VertexShader>(0);
	useShader<ID3D11PixelShader>(1);
};
services::Direct3D11Graphics::~Direct3D11Graphics( void )
{
	_factory->Release();
	_swapChain->Release();
	_device->Release();
	_deviceContext->Release();
};
void services::Direct3D11Graphics::draw( const Vertex vertexes[],
										int vertexesSize,
										const int indices[],
										int indicesSize )
{
	float color[] = { 0.f, 0.f, 0.f, 0.f };
	ID3D11Buffer* buffer;
	WVPMatrix mat; 

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof( Vertex )*vertexesSize;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResDat;
	subResDat.pSysMem = vertexes;
	subResDat.SysMemPitch = 0;
	subResDat.SysMemSlicePitch = 0;

	HRESULT hr = _device->CreateBuffer( &bufferDesc, &subResDat, &buffer );
	if ( FAILED(hr) )
	{
		throw "Erreur buffer vertices";
	}

	UINT stride = sizeof( Vertex );
	UINT offset = 0;
	_deviceContext->IASetVertexBuffers( 0, 1, &buffer, &stride, &offset );
	
	bufferDesc.ByteWidth = sizeof( int )*indicesSize;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	subResDat.pSysMem = indices;
	subResDat.SysMemPitch = 0;
	subResDat.SysMemSlicePitch = 0;

	hr = _device->CreateBuffer( &bufferDesc, &subResDat, &buffer );
	if ( FAILED(hr) )
	{
		throw "Erreur buffer indices";
	}
	_deviceContext->IASetIndexBuffer( buffer, DXGI_FORMAT_R32_UINT, 0 );

	bufferDesc.ByteWidth = sizeof( WVPMatrix );
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	
	//mat.mat = DirectX::XMMatrixTranspose(_projectionMatrix)*DirectX::XMMatrixTranspose(_viewMatrix);
	/*
	subResDat.pSysMem = &mat;
	subResDat.SysMemPitch = 0;
	subResDat.SysMemSlicePitch = 0;
	*/
	hr = _device->CreateBuffer( &bufferDesc, 0/*&subResDat*/, &buffer );

	if ( FAILED(hr) )
	{
		throw "Erreur buffer matrice";
	}

	//mat.mat = DirectX::XMMatrixTranspose( _viewMatrix*_projectionMatrix );
	mat.mat = DirectX::XMMatrixTranspose(_projectionMatrix)*DirectX::XMMatrixTranspose(_viewMatrix);
	/*
    DirectX::XMVECTOR Eye = DirectX::XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    DirectX::XMVECTOR At = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    DirectX::XMVECTOR Up = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    mat.mat = XMMatrixLookAtLH( Eye, At, Up )*;
	*/
	_deviceContext->VSSetConstantBuffers( 0, 1, &buffer );

	_deviceContext->UpdateSubresource( buffer, 0, 0, &mat, 0, 0 );
	
	_deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	
	_deviceContext->ClearRenderTargetView( _renderTarget, color );

	_deviceContext->DrawIndexed( indicesSize, 0, 0 );
	_swapChain->Present(0, 0);
};
void services::Direct3D11Graphics::setCamera(
	float eyeX, float eyeY, float eyeZ,
	float atX, float atY, float atZ,
	float upX, float upY, float upZ
)
{
	_viewMatrix = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet( eyeX, eyeY, eyeZ, 0.f ),
		DirectX::XMVectorSet( atX, atY, atZ, 0.f ),
		DirectX::XMVectorSet( upX, upY, upZ, 0.f )
	);
};
void services::Direct3D11Graphics::setPerspective(
	float fovAngleY, float ratio, float nearZ, float farZ
)
{
	_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(
		fovAngleY, ratio, nearZ, farZ
	);
};
template<class Shader> void services::Direct3D11Graphics::loadShader( UINT16 key, ID3D10Blob* shaderBlob )
{
	Shader* shader = 0;
	pair<map<UINT16, ID3D11DeviceChild*>::const_iterator, bool> ret;

	_loadShader( shaderBlob, shader );
	ret = _shaders.insert(
		pair<UINT16, ID3D11DeviceChild*>(
			key,
			shader
		)
	);
	if ( !ret.second )
	{
		throw "Shader already inserted";
	}
};
template<class Shader> void services::Direct3D11Graphics::useShader( UINT16 key )
{
	map<UINT16, ID3D11DeviceChild*>::const_iterator element = _shaders.find( key );
	if ( element != _shaders.end() )
	{
		_useShader( (Shader*)(element->second) );
	}
};
void services::Direct3D11Graphics::_useShader( ID3D11VertexShader* shader )
{
	_deviceContext->VSSetShader( shader, 0, 0 );
};
void services::Direct3D11Graphics::_useShader( ID3D11HullShader* shader )
{
	_deviceContext->HSSetShader( shader, 0, 0 );
};
void services::Direct3D11Graphics::_useShader( ID3D11DomainShader* shader )
{
	_deviceContext->DSSetShader( shader, 0, 0 );
};
void services::Direct3D11Graphics::_useShader( ID3D11GeometryShader* shader )
{
	_deviceContext->GSSetShader( shader, 0, 0 );
};
void services::Direct3D11Graphics::_useShader( ID3D11PixelShader* shader )
{
	_deviceContext->PSSetShader( shader, 0, 0 );
};
void services::Direct3D11Graphics::_createInputLayout( ID3D10Blob* shaderBlob )
{
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{"SV_Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		/*{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
			D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}*/
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	int ied = sizeof(inputElementDesc);
	int sdesc = sizeof(D3D11_INPUT_ELEMENT_DESC);
	HRESULT hr = _device->CreateInputLayout(
		inputElementDesc,
		sizeof(inputElementDesc) / sizeof(D3D11_INPUT_ELEMENT_DESC),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&_inputLayout
	);
	if ( FAILED(hr) )
	{
		throw "Failed to create input layout";
	}
	_deviceContext->IASetInputLayout( _inputLayout );
};
void services::Direct3D11Graphics::_loadShader( ID3D10Blob* shaderBlob, ID3D11VertexShader*& shader )
{
	
	_device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		0,
		&shader
	);
	_createInputLayout( shaderBlob );
};
void services::Direct3D11Graphics::_loadShader( ID3D10Blob* shaderBlob, ID3D11HullShader*& shader )
{
	_device->CreateHullShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		0,
		&shader
	);
};
void services::Direct3D11Graphics::_loadShader( ID3D10Blob* shaderBlob, ID3D11DomainShader*& shader )
{
	_device->CreateDomainShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		0,
		&shader
	);
};
void services::Direct3D11Graphics::_loadShader( ID3D10Blob* shaderBlob, ID3D11GeometryShader*& shader )
{
	_device->CreateGeometryShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		0,
		&shader
	);
};
void services::Direct3D11Graphics::_loadShader( ID3D10Blob* shaderBlob, ID3D11PixelShader*& shader )
{
	_device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		0,
		&shader
	);
};
void services::Direct3D11Graphics::_initDeviceAndSwapChain( void )
{
	D3D_FEATURE_LEVEL features[] = {
		D3D_FEATURE_LEVEL_11_0,
	};

	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	swapChainDesc.BufferDesc.Width						= WIDTH;
	swapChainDesc.BufferDesc.Height						= HEIGHT;
	swapChainDesc.BufferDesc.RefreshRate.Numerator		= FRAMERATE_NUM;
	swapChainDesc.BufferDesc.RefreshRate.Denominator	= FRAMERATE_DEN;
	swapChainDesc.BufferDesc.ScanlineOrdering			=
		DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	swapChainDesc.BufferDesc.Format						=
		DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Scaling					=
		DXGI_MODE_SCALING_STRETCHED;

	swapChainDesc.SampleDesc.Count		= 1;
	swapChainDesc.SampleDesc.Quality	= 0;

	swapChainDesc.BufferUsage	= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount	= 1;
	swapChainDesc.OutputWindow	= _window;
	swapChainDesc.Windowed		= true;
	swapChainDesc.SwapEffect	= DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags			= 0;

	D3D_FEATURE_LEVEL feature_returned;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		0,							// Adapter (Carte graphique)
		D3D_DRIVER_TYPE_HARDWARE,	// Driver
		0,							// Software rasterizer
		D3D11_CREATE_DEVICE_DEBUG,							// Flags
		features,                   // Liste des versions
		ARRAYSIZE(features),		// Taille de la liste des versions
		D3D11_SDK_VERSION,			// SDK
		// Swap chain
		&swapChainDesc,				// Description du swap chain
		&_swapChain,				// Swap chain
		// Device
		&_device,					// Device
		&feature_returned,			// Version choisie
		&_deviceContext				// Device Context
	);

	if ( FAILED(hr) )
	{
		throw "Impossible de créer le device Direct3D et le swap chain";
	}
};
void services::Direct3D11Graphics::_initRenderTarget( void )
{
	ID3D11Texture2D* buffer = 0;

	HRESULT hr = _swapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&buffer
	);

	if ( FAILED(hr) )
	{
		throw "Impossible de récupérer le buffer du swap chain";
	}

	hr = _device->CreateRenderTargetView(
		buffer,
		0,
		&_renderTarget
	);
	buffer->Release();

	_deviceContext->OMSetRenderTargets(
		1,
		&_renderTarget,
		0	// Depth stencil buffer
	);
};
void services::Direct3D11Graphics::_initViewport( void )
{
	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Height	= HEIGHT;
	viewport.Width	= WIDTH;
	viewport.MinDepth = 0.f;
	viewport.MaxDepth = 1.0f;

	_deviceContext->RSSetViewports(
		1,
		&viewport
	);
};
IDXGIFactory* services::Direct3D11Graphics::_getFactory( void )
{
	if ( _factory == 0 )
	{
		CreateDXGIFactory(
			__uuidof(IDXGIFactory),
			(void**)(&_factory)
		);
	}
	return _factory;
};