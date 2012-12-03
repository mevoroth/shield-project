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
const Mesh* FbxMeshLoader::load( const std::string& filename )
{
	FbxScene* scene = FbxScene::Create( _sdkManager, "scene" );
	FbxMesh* mesh = new FbxMesh();

	_importer->Initialize(
		filename.c_str(),
		-1,
		_sdkManager->GetIOSettings()
	);
	_importer->Import(scene);
	for ( int i = 0, c = scene->GetNodeCount(); i < c; ++i )
	{
		if ( !scene->GetNode(i)->GetNodeAttribute()
			|| scene->GetNode(i)->GetNodeAttribute()->GetAttributeType()
			!= FbxNodeAttribute::eMesh )
		{
			continue;
		}
		fbxsdk_2013_3::FbxMesh* fbxmesh = (fbxsdk_2013_3::FbxMesh*)scene->GetNode(i)->GetNodeAttribute();
		FbxVector4* vertexes = fbxmesh->GetControlPoints();
		int vertexesCount = fbxmesh->GetControlPointsCount();
		int polygonCount = fbxmesh->GetPolygonCount();

		for ( int vertexIndex = 0; vertexIndex < vertexesCount; ++vertexIndex )
		{
			structs::Vertex v;
			
			// Get vertex
			v.pos = DirectX::XMFLOAT3(
				vertexes[vertexIndex][0],
				vertexes[vertexIndex][1],
				vertexes[vertexIndex][2]
			);

			// Get normals
			_getNormal(fbxmesh, vertexIndex, &v.norm);

			//TODO: TEXTURE
			mesh->putVertex( v );
		}
			
		for ( int j = 0; j < polygonCount; ++j )
		{
			int polygonSize = fbxmesh->GetPolygonSize( j );
			if ( polygonSize == 3 )
			{
				mesh->putTriangle(
					fbxmesh->GetPolygonVertex(j, 0),
					fbxmesh->GetPolygonVertex(j, 1),
					fbxmesh->GetPolygonVertex(j, 2)
				);
			}
			else // Quadrilatère
			{
				mesh->putTriangle(
					fbxmesh->GetPolygonVertex(j, 0),
					fbxmesh->GetPolygonVertex(j, 1),
					fbxmesh->GetPolygonVertex(j, 2)
				);
				mesh->putTriangle(
					fbxmesh->GetPolygonVertex(j, 0),
					fbxmesh->GetPolygonVertex(j, 2),
					fbxmesh->GetPolygonVertex(j, 3)
				);
			}
		}
	}
	return mesh;
};
void FbxMeshLoader::_getNormal(
	const fbxsdk_2013_3::FbxMesh* mesh,
	int vertex,
	DirectX::XMFLOAT3* normal
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
		
		if ( normalIndex > 0 )
		{
			FbxVector4 fbxNormal = normalEl->GetDirectArray()
				.GetAt( normalIndex );
			DirectX::XMVECTOR length = DirectX::XMVectorSet(
				fbxNormal[0],
				fbxNormal[1],
				fbxNormal[2],
				0.f
			);
			
			length = DirectX::XMVector3Length( length );

			normal->x = fbxNormal[0]/length.vector4_f32[0];
			normal->y = fbxNormal[1]/length.vector4_f32[0];
			normal->z = fbxNormal[2]/length.vector4_f32[0];
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
