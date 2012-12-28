#include "Direct3D11Graphics.h"

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "WVPMatrix.h"

#include "..\..\libs\DDSTextureLoader.h"

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
	ID3D10Blob* geometryShader = 0;
	ID3D10Blob* errors = 0;
	HRESULT hr = D3DCompileFromFile( L"testvs.hlsl", 0, 0, "VS", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG, 0, &vertexShader, &errors );
	if ( FAILED(hr) )
	{
		int strsize = errors->GetBufferSize();
		std::string str = (char*)errors->GetBufferPointer();
		throw "Erreur";
	}
	loadShader<ID3D11VertexShader>(0, vertexShader);
	createConstantBuffer(
		0,
		0,
		sizeof(WVPMatrix)
	);
	hr = D3DCompileFromFile( L"testps.hlsl", 0, 0, "PS", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG, 0, &pixelShader, &errors );
	if ( FAILED(hr) )
	{
		char* str = (char*)errors->GetBufferPointer();
		throw "Erreur";
	}
	loadShader<ID3D11PixelShader>(1, pixelShader);
	hr = D3DCompileFromFile( L"testgs.hlsl", 0, 0, "GS", "gs_5_0", D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG, 0, &geometryShader, &errors );
	if ( FAILED(hr) )
	{
		int strsize = errors->GetBufferSize();
		std::string str = (char*)errors->GetBufferPointer();
		throw "Erreur";
	}
	loadShader<ID3D11GeometryShader>(2, geometryShader);
};
services::Direct3D11Graphics::~Direct3D11Graphics( void )
{
	_factory->Release();
	_swapChain->Release();
	_device->Release();
	_deviceContext->Release();
};
void services::Direct3D11Graphics::begin( void )
{
	float color[] = { 0.f, 0.f, 0.f, 0.f };
	_deviceContext->ClearRenderTargetView( _renderTarget, color );
	_deviceContext->ClearDepthStencilView( _depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
};
void services::Direct3D11Graphics::end( void )
{
	_swapChain->Present(0, 0);
};
void services::Direct3D11Graphics::draw( const Vertex vertexes[],
										int vertexesSize,
										const wchar_t* texture )
{
	ID3D11Buffer* vertexBuffer;
	WVPMatrix mat;
	ID3D11ShaderResourceView* texResource;
	
	loadTexture( texture, texResource );
	setShaderResource( 1, 0, texResource );

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 0;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.BorderColor[0] = 0.f;
	samplerDesc.BorderColor[1] = 0.f;
	samplerDesc.BorderColor[2] = 0.f;
	samplerDesc.BorderColor[3] = 0.f;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	setSamplerState( 1, 0, samplerDesc );

	useShader<ID3D11VertexShader>(0);
	useShader<ID3D11PixelShader>(1);
	useShader<ID3D11GeometryShader>(2);

	_createVertexBuffer( vertexes, vertexesSize, vertexBuffer );

	mat.mat = _projectionMatrix*_viewMatrix;
	updateConstantBuffer( 0, 0, &mat );

	_deviceContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);
	
	// Draw
	_deviceContext->Draw( vertexesSize, 0 );

	// Clean
	vertexBuffer->Release();
};
void services::Direct3D11Graphics::loadTexture(
	const wchar_t* texture,
	ID3D11ShaderResourceView*& resource
)
{
	map<const wchar_t*, ID3D11ShaderResourceView*>::iterator texResource =
		_textures.find( texture );

	if ( texResource == _textures.end() )
	{
		wchar_t* path = new wchar_t[24 + wcslen(texture)];
		wcscpy( path, L"resources\\textures\\" );
		wcscat( path, texture );
		wcscat( path, L".dds" );

		HRESULT hr = DirectX::CreateDDSTextureFromFile( _device, path, 0, &resource );
		delete path;
		if ( FAILED(hr) )
		{
			throw;
		}
		_textures.insert(
			pair<const wchar_t*, ID3D11ShaderResourceView*>(
				texture,
				resource
			)
		);
	}
	else
	{
		resource = texResource->second;
	}
}
void services::Direct3D11Graphics::setSamplerState(
	UINT16 shader,
	UINT16 slot,
	const D3D11_SAMPLER_DESC& samplerDesc
)
{
	ID3D11SamplerState* state;
	HRESULT hr = _device->CreateSamplerState( &samplerDesc, &state );
	
	map<
		UINT16,
		map<UINT16, ID3D11SamplerState*>
	>::iterator samplerState = _samplerStates.find( shader );
	if ( samplerState == _samplerStates.end() )
	{
		throw;
	}

	map<UINT16, ID3D11SamplerState*>::iterator samplerSlot =
		samplerState->second.find( slot );
	if ( samplerSlot == samplerState->second.end() )
	{
		samplerState->second.insert(
			pair<UINT16, ID3D11SamplerState*>(
				slot,
				state
			)
		);
	}
	else
	{
		samplerSlot->second->Release();
		samplerSlot->second = state;
	}
};
void services::Direct3D11Graphics::setShaderResource(
	UINT16 shader,
	UINT16 slot,
	ID3D11ShaderResourceView* resource
)
{
	map<
		UINT16,
		map<UINT16, ID3D11ShaderResourceView*>
	>::iterator shaderResource = _shaderResources.find( shader );
	if ( shaderResource == _shaderResources.end() )
	{
		throw;
	}
	map<UINT16, ID3D11ShaderResourceView*>::iterator resourceSlot =
		shaderResource->second.find( slot );
	if ( resourceSlot == shaderResource->second.end() )
	{
		shaderResource->second.insert(
			pair<UINT16, ID3D11ShaderResourceView*>(
				slot,
				resource
			)
		);
	}
	else
	{
		resourceSlot->second = resource;
	}
};
void services::Direct3D11Graphics::setCamera(
	float eyeX, float eyeY, float eyeZ,
	float atX, float atY, float atZ,
	float upX, float upY, float upZ
)
{
	_viewMatrix = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet( eyeX, eyeY, eyeZ, 0.f ),
			DirectX::XMVectorSet( atX, atY, atZ, 0.f ),
			DirectX::XMVectorSet( upX, upY, upZ, 0.f )
		)
	);
};
void services::Direct3D11Graphics::setPerspective(
	float fovAngleY, float ratio, float nearZ, float farZ
)
{
	_projectionMatrix = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			fovAngleY, ratio, nearZ, farZ
		)
	);
};
void services::Direct3D11Graphics::updateConstantBuffer(
	UINT16 shader,
	UINT16 slot,
	void* resource
)
{
	map<UINT16, map<UINT16, ID3D11Buffer*>>::const_iterator constBuffer =
		_constantBuffers.find( shader );
	if ( constBuffer == _constantBuffers.end() )
	{
		throw;
	}
	map<UINT16, ID3D11Buffer*>::const_iterator bufferSlot =
		constBuffer->second.find( slot );
	if ( bufferSlot == constBuffer->second.end() )
	{
		throw;
	}
	_deviceContext->UpdateSubresource(
		bufferSlot->second,
		0,
		0,
		resource,
		0,
		0
	);
};
void services::Direct3D11Graphics::createConstantBuffer(
	UINT16 shader,
	UINT16 slot,
	int size
)
{
	D3D11_BUFFER_DESC bufferDesc;
	HRESULT hr;
	ID3D11Buffer* buffer;
	pair<map<UINT16, ID3D11Buffer*>::const_iterator, bool> ret;

	map<UINT16, map<UINT16, ID3D11Buffer*>>::iterator constBuffer =
		_constantBuffers.find( shader );
	if ( constBuffer == _constantBuffers.end() )
	{
		throw;
	}
	
	bufferDesc.ByteWidth = size;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	
	hr = _device->CreateBuffer( &bufferDesc, 0, &buffer );

	if ( FAILED(hr) )
	{
		throw "Erreur buffer matrice";
	}

	ret = constBuffer->second.insert(
		pair<UINT16, ID3D11Buffer*>(
			slot,
			buffer
		)
	);
	if ( !ret.second )
	{
		buffer->Release();
		throw;
	}
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
	_constantBuffers.insert(
		pair<UINT16, map<UINT16, ID3D11Buffer*>>(
			key,
			map<UINT16, ID3D11Buffer*>()
		)
	);
	_shaderResources.insert(
		pair<UINT16, map<UINT16, ID3D11ShaderResourceView*>>(
			key,
			map<UINT16, ID3D11ShaderResourceView*>()
		)
	);
	_samplerStates.insert(
		pair<UINT16, map<UINT16, ID3D11SamplerState*>>(
			key,
			map<UINT16, ID3D11SamplerState*>()
		)
	);
};
template<class Shader> void services::Direct3D11Graphics::useShader(
	UINT16 key
)
{
	map<UINT16, ID3D11DeviceChild*>::const_iterator element =
		_shaders.find( key );
	map<UINT16, map<UINT16, ID3D11Buffer*>>::const_iterator constBuffers =
		_constantBuffers.find( key );
	map<
		UINT16,
		map<UINT16, ID3D11ShaderResourceView*>
	>::const_iterator shaderResources = _shaderResources.find( key );
	map<
		UINT16,
		map<UINT16, ID3D11SamplerState*>
	>::const_iterator samplerStates = _samplerStates.find( key );
	
	if ( element != _shaders.end()
		&& constBuffers != _constantBuffers.end()
		&& shaderResources != _shaderResources.end()
		&& samplerStates != _samplerStates.end() )
	{
		_useShader(
			(Shader*)(element->second),
			constBuffers->second,
			shaderResources->second,
			samplerStates->second
		);
	}
};
void services::Direct3D11Graphics::_useShader(
	ID3D11VertexShader* shader,
	const map<UINT16, ID3D11Buffer*>& buffers,
	const map<UINT16, ID3D11ShaderResourceView*>& resources,
	const map<UINT16, ID3D11SamplerState*>& states
)
{
	_deviceContext->VSSetShader( shader, 0, 0 );
	for (
		map<UINT16, ID3D11Buffer*>::const_iterator it = buffers.begin();
		it != buffers.end();
		++it
	)
	{
		_deviceContext->VSSetConstantBuffers( it->first, 1, &it->second );
	}
	for (
		map<UINT16,
			ID3D11ShaderResourceView*>::const_iterator it = resources.begin();
		it != resources.end();
		++it
	)
	{
		_deviceContext->VSSetShaderResources( it->first, 1, &it->second );
	}
	for (
		map<UINT16, ID3D11SamplerState*>::const_iterator it = states.begin();
		it != states.end();
		++it
	)
	{
		_deviceContext->VSSetSamplers( it->first, 1, &it->second );
	}
};
void services::Direct3D11Graphics::_useShader(
	ID3D11HullShader* shader,
	const map<UINT16, ID3D11Buffer*>& buffers,
	const map<UINT16, ID3D11ShaderResourceView*>& resources,
	const map<UINT16, ID3D11SamplerState*>& states
)
{
	_deviceContext->HSSetShader( shader, 0, 0 );
	for (
		map<UINT16, ID3D11Buffer*>::const_iterator it = buffers.begin();
		it != buffers.end();
		++it
	)
	{
		_deviceContext->HSSetConstantBuffers( it->first, 1, &it->second );
	}
	for (
		map<UINT16,
			ID3D11ShaderResourceView*>::const_iterator it = resources.begin();
		it != resources.end();
		++it
	)
	{
		_deviceContext->HSSetShaderResources( it->first, 1, &it->second );
	}
	for (
		map<UINT16, ID3D11SamplerState*>::const_iterator it = states.begin();
		it != states.end();
		++it
	)
	{
		_deviceContext->HSSetSamplers( it->first, 1, &it->second );
	}
};
void services::Direct3D11Graphics::_useShader(
	ID3D11DomainShader* shader,
	const map<UINT16, ID3D11Buffer*>& buffers,
	const map<UINT16, ID3D11ShaderResourceView*>& resources,
	const map<UINT16, ID3D11SamplerState*>& states
)
{
	_deviceContext->DSSetShader( shader, 0, 0 );
	for (
		map<UINT16, ID3D11Buffer*>::const_iterator it = buffers.begin();
		it != buffers.end();
		++it
	)
	{
		_deviceContext->DSSetConstantBuffers( it->first, 1, &it->second );
	}
	for (
		map<UINT16,
			ID3D11ShaderResourceView*>::const_iterator it = resources.begin();
		it != resources.end();
		++it
	)
	{
		_deviceContext->DSSetShaderResources( it->first, 1, &it->second );
	}
	for (
		map<UINT16, ID3D11SamplerState*>::const_iterator it = states.begin();
		it != states.end();
		++it
	)
	{
		_deviceContext->DSSetSamplers( it->first, 1, &it->second );
	}
};
void services::Direct3D11Graphics::_useShader(
	ID3D11GeometryShader* shader,
	const map<UINT16, ID3D11Buffer*>& buffers,
	const map<UINT16, ID3D11ShaderResourceView*>& resources,
	const map<UINT16, ID3D11SamplerState*>& states
)
{
	_deviceContext->GSSetShader( shader, 0, 0 );
	for (
		map<UINT16, ID3D11Buffer*>::const_iterator it = buffers.begin();
		it != buffers.end();
		++it
	)
	{
		_deviceContext->GSSetConstantBuffers( it->first, 1, &it->second );
	}
	for (
		map<UINT16,
			ID3D11ShaderResourceView*>::const_iterator it = resources.begin();
		it != resources.end();
		++it
	)
	{
		_deviceContext->GSSetShaderResources( it->first, 1, &it->second );
	}
	for (
		map<UINT16, ID3D11SamplerState*>::const_iterator it = states.begin();
		it != states.end();
		++it
	)
	{
		_deviceContext->GSSetSamplers( it->first, 1, &it->second );
	}
};
void services::Direct3D11Graphics::_useShader(
	ID3D11PixelShader* shader,
	const map<UINT16, ID3D11Buffer*>& buffers,
	const map<UINT16, ID3D11ShaderResourceView*>& resources,
	const map<UINT16, ID3D11SamplerState*>& states
)
{
	_deviceContext->PSSetShader( shader, 0, 0 );
	for (
		map<UINT16, ID3D11Buffer*>::const_iterator it = buffers.begin();
		it != buffers.end();
		++it
	)
	{
		_deviceContext->PSSetConstantBuffers( it->first, 1, &it->second );
	}
	for (
		map<UINT16,
			ID3D11ShaderResourceView*>::const_iterator it = resources.begin();
		it != resources.end();
		++it
	)
	{
		_deviceContext->PSSetShaderResources( it->first, 1, &it->second );
	}
	for (
		map<UINT16, ID3D11SamplerState*>::const_iterator it = states.begin();
		it != states.end();
		++it
	)
	{
		_deviceContext->PSSetSamplers( it->first, 1, &it->second );
	}
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
			D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

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

	D3D11_TEXTURE2D_DESC tex2DDesc;
	tex2DDesc.Width = 1920;
	tex2DDesc.Height = 1080;
	tex2DDesc.MipLevels = 1;
	tex2DDesc.ArraySize = 1;
	tex2DDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex2DDesc.SampleDesc.Count = 1;
	tex2DDesc.SampleDesc.Quality = 0;
	tex2DDesc.Usage = D3D11_USAGE_DEFAULT;
	tex2DDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex2DDesc.CPUAccessFlags = 0;
	tex2DDesc.MiscFlags = 0;

	_device->CreateTexture2D( &tex2DDesc, 0, &buffer );

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	depthStencilViewDesc.Format = tex2DDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	_device->CreateDepthStencilView( buffer, &depthStencilViewDesc, &_depthStencilView );

	_deviceContext->OMSetRenderTargets(
		1,
		&_renderTarget,
		_depthStencilView	// Depth stencil buffer
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
void services::Direct3D11Graphics::_createVertexBuffer(
	const Vertex vertexes[],
	int vertexesSize,
	ID3D11Buffer*& buffer
)
{
	D3D11_BUFFER_DESC bufferDesc;
	D3D11_SUBRESOURCE_DATA subResDat;
	
	UINT stride = sizeof( Vertex );
	UINT offset = 0;
	HRESULT hr;

	bufferDesc.ByteWidth = sizeof( Vertex )*vertexesSize;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	subResDat.pSysMem = vertexes;
	subResDat.SysMemPitch = 0;
	subResDat.SysMemSlicePitch = 0;

	hr = _device->CreateBuffer( &bufferDesc, &subResDat, &buffer );
	if ( FAILED(hr) )
	{
		throw "Erreur buffer vertices";
	}

	_deviceContext->IASetVertexBuffers( 0, 1, &buffer, &stride, &offset );
};
