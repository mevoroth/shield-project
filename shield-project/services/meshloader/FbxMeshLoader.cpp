#include "FbxMeshLoader.h"
#include "FbxMesh.h"
#include <DirectXMath.h>

using namespace shield::services;

FbxMeshLoader::FbxMeshLoader()
	: _sdkManager( FbxManager::Create() )
{
	FbxIOSettings* iosettings = FbxIOSettings::Create( _sdkManager, IOSROOT );
	iosettings->SetBoolProp( IMP_FBX_MATERIAL,			true );
	iosettings->SetBoolProp( IMP_FBX_TEXTURE,			true );
	iosettings->SetBoolProp( IMP_FBX_LINK,				false );
	iosettings->SetBoolProp( IMP_FBX_SHAPE,				false );
	iosettings->SetBoolProp( IMP_FBX_GOBO,				false );
	iosettings->SetBoolProp( IMP_FBX_ANIMATION,			true );
	iosettings->SetBoolProp( IMP_FBX_GLOBAL_SETTINGS,	true );
	_sdkManager->SetIOSettings( iosettings );

	_importer = FbxImporter::Create( _sdkManager, "" );
};
FbxMeshLoader::~FbxMeshLoader()
{
	_importer->Destroy();
	_sdkManager->Destroy();
};
vector<Mesh*> FbxMeshLoader::load( const string& filename )
{
	vector<Mesh*> meshes;

	map<string, vector<Mesh*>>::iterator mesh = _cache.find( filename );

	if ( mesh == _cache.end() )
	{
		_createMeshes( filename, meshes );
		_normalize( meshes );
		_cache.insert(
			pair<string, vector<Mesh*>>(
				filename,
				meshes
			)
		);
	}
	else
	{
		meshes = mesh->second;
	}

	return _clone( meshes );
};
void FbxMeshLoader::_normalize( vector<Mesh*>& meshes )
{
	float xmin = std::numeric_limits<float>::infinity();
	float xmax = -xmin;
	float ymin = xmin;
	float ymax = xmax;
	float zmin = xmin;
	float zmax = xmax;

	for ( vector<Mesh*>::const_iterator mesh = meshes.begin();
		mesh != meshes.end();
		++mesh )
	{
		vector<structs::Vertex>* vertexes = (*mesh)->getVertexes();
		for ( vector<structs::Vertex>::const_iterator vertex = vertexes->begin();
			vertex != vertexes->end();
			++vertex )
		{
			xmin = min( xmin, vertex->pos.x );
			ymin = min( ymin, vertex->pos.y );
			zmin = min( zmin, vertex->pos.z );
			xmax = max( xmax, vertex->pos.x );
			ymax = max( ymax, vertex->pos.y );
			zmax = max( zmax, vertex->pos.z );
		}
	}
	xmin = abs( xmin );
	ymin = abs( ymin );
	zmin = abs( zmin );
	xmax = abs( xmax ) + xmin;
	ymax = abs( ymax ) + ymin;
	zmax = abs( zmax ) + zmin;
	ymax = max( max(xmax, ymax), zmax );
	for ( vector<Mesh*>::iterator mesh = meshes.begin();
		mesh != meshes.end();
		++mesh )
	{
		((FbxMesh*)*mesh)->normalize(
			ymax,
			structs::Vector3(xmin, ymin, zmin),
			structs::Vector3((ymax - xmax)/2.f, 0.f, (ymax - zmax)/2.f)
		);
	}
};
vector<Mesh*> FbxMeshLoader::_clone( const vector<Mesh*>& meshes )
{
	vector<Mesh*> clone;

	for ( vector<Mesh*>::const_iterator it = meshes.begin();
		it != meshes.end();
		++it )
	{
		FbxMesh* mesh = new FbxMesh( *(FbxMesh*)*it );
		clone.push_back( mesh );
	}

	return clone;
};
void FbxMeshLoader::_createMeshes( const string& filename, vector<Mesh*>& meshes )
{
	FbxScene* scene = FbxScene::Create( _sdkManager, "scene" );

	_importer->Initialize(
		filename.c_str(),
		-1,
		_sdkManager->GetIOSettings()
	);
	_importer->Import( scene );
	for ( int i = 0, c = scene->GetNodeCount(); i < c; ++i )
	{
		if ( !scene->GetNode(i)->GetNodeAttribute()
			|| scene->GetNode(i)->GetNodeAttribute()->GetAttributeType()
			!= FbxNodeAttribute::eMesh )
		{
			continue;
		}
		FbxMesh* mesh = new FbxMesh();

		string fname = string( scene->GetNode(i)->GetName() );
		wchar_t* fnamewide = new wchar_t[fname.size() + 1];
		mbstowcs( fnamewide, fname.c_str(), 255 );
		mesh->setTexture( fnamewide );

		fbxsdk_2013_3::FbxMesh* fbxmesh = (fbxsdk_2013_3::FbxMesh*)scene->GetNode(i)->GetNodeAttribute();
		FbxVector4* vertexes = fbxmesh->GetControlPoints();
		int vertexesCount = fbxmesh->GetControlPointsCount();
		int polygonCount = fbxmesh->GetPolygonCount();
		DirectX::XMFLOAT3* normals = new DirectX::XMFLOAT3[vertexesCount];
		
		for ( int vertexIndex = 0; vertexIndex < vertexesCount; ++vertexIndex )
		{
			// Get normals
			_getNormal( fbxmesh, vertexIndex, normals[vertexIndex] );
		}
		
		for ( int p = 0; p < polygonCount; ++p )
		{
			int polygonSize = fbxmesh->GetPolygonSize( p );
			structs::Vertex* polygonVertexes = new structs::Vertex[polygonSize];
			for ( int v = 0; v < polygonSize; ++v )
			{
				FbxVector2 uv;

				_getUV( fbxmesh, p, v, uv );
				_createVertex(
					vertexes,
					normals,
					fbxmesh->GetPolygonVertex(p, v),
					uv,
					polygonVertexes[v]
				);
			}
			mesh->putTriangle(
				polygonVertexes[0],
				polygonVertexes[1],
				polygonVertexes[2]
			);

			if ( polygonSize == 4 ) // Quadrilatère
			{
				mesh->putTriangle(
					polygonVertexes[0],
					polygonVertexes[2],
					polygonVertexes[3]
				);
			}
			delete polygonVertexes;
		}
		meshes.push_back( mesh );
		delete normals;
	}
};
void FbxMeshLoader::_createVertex(
	const FbxVector4* vertexes,
	const DirectX::XMFLOAT3* normals,
	int vertexIndex,
	const FbxVector2& uv,
	shield::structs::Vertex& v
) const
{
	v.pos = DirectX::XMFLOAT3(
		vertexes[vertexIndex][0],
		vertexes[vertexIndex][1],
		vertexes[vertexIndex][2]
	);
	v.norm = normals[vertexIndex];
	v.tex = DirectX::XMFLOAT2(
		uv[0],
		uv[1]
	);
};
void FbxMeshLoader::_getUV(
	fbxsdk_2013_3::FbxMesh* mesh,
	int polygon,
	int vertex,
	FbxVector2& uv
) const
{
	if ( mesh->GetElementUVCount() <= 0 )
	{
		throw;
	}
	FbxGeometryElementUV* elUV = mesh->GetElementUV(0);
	if ( elUV->GetMappingMode() == FbxGeometryElement::eByPolygonVertex )
	{
		int texIndex = mesh->GetTextureUVIndex(polygon, vertex);
		switch ( elUV->GetReferenceMode() )
		{
		case FbxGeometryElement::eDirect:
		case FbxGeometryElement::eIndexToDirect:
			uv = elUV->GetDirectArray().GetAt( texIndex );
		}
	}
};
void FbxMeshLoader::_getNormal(
	const fbxsdk_2013_3::FbxMesh* mesh,
	int vertex,
	DirectX::XMFLOAT3& normal
) const
{
	const FbxGeometryElementNormal* normalEl = mesh->GetElementNormal();
	if (!normalEl)
	{
		throw;
	}
	if ( normalEl->GetMappingMode() == FbxGeometryElement::eByControlPoint )
	{
		int normalIndex = -1;
		if ( normalEl->GetReferenceMode() == FbxGeometryElement::eDirect )
		{
			normalIndex = vertex;
		}
		else if ( normalEl->GetReferenceMode()
			== FbxGeometryElement::eIndexToDirect )
		{
			normalIndex = normalEl->GetIndexArray().GetAt( vertex );
		}
		
		if ( normalIndex >= 0 )
		{
			FbxVector4 fbxNormal = normalEl->GetDirectArray()
				.GetAt( normalIndex );
			float length = DirectX::XMVectorGetX(
				DirectX::XMVector3Length(
					DirectX::XMVectorSet(
						fbxNormal[0],
						fbxNormal[1],
						fbxNormal[2],
						0.f
					)
				)
			);

			normal.x = fbxNormal[0]/length;
			normal.y = fbxNormal[1]/length;
			normal.z = fbxNormal[2]/length;
		}
	}
	else if ( normalEl->GetMappingMode()
		== FbxGeometryElement::eByPolygonVertex )
	{
		// TODO: Polygon Vertex
		// Lol ! Go convert your mesh ! Dun wana code dat shit !
		throw;
	}
};
