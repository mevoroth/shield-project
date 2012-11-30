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
		if ( scene->GetNode(i)->GetNodeAttribute() != 0
			&& scene->GetNode(i)->GetNodeAttribute()->GetAttributeType()
			== FbxNodeAttribute::eMesh )
		{
			fbxsdk_2013_3::FbxMesh* fbxmesh = (fbxsdk_2013_3::FbxMesh*)scene->GetNode(i)->GetNodeAttribute();
			FbxVector4* vertexes = fbxmesh->GetControlPoints();
			FbxVector4 v0 = vertexes[0];
			FbxVector4 v1 = vertexes[1];
			FbxVector4 v2 = vertexes[2];
			FbxVector4 v3 = vertexes[3];
			//FbxVector4 v4 = vertexes[4];
			int vertexesCount = fbxmesh->GetControlPointsCount();

			for ( int i = 0; i < vertexesCount; ++i )
			{
				structs::Vertex v;
				v.pos = DirectX::XMFLOAT3(
					vertexes[i].mData[0],
					vertexes[i].mData[1],
					vertexes[i].mData[2]
				);
				//TODO: NORMALE + TEXTURE
				mesh->putVertex( v );
			}

			int polygonCount = fbxmesh->GetPolygonCount();
			for ( int j = 0; j < polygonCount; ++j )
			{
				int polygonSize = fbxmesh->GetPolygonSize( j );
				int i0 = fbxmesh->GetPolygonVertex(j, 0);
				int i1 = fbxmesh->GetPolygonVertex(j, 1);
				int i2 = fbxmesh->GetPolygonVertex(j, 2);
				int i3 = fbxmesh->GetPolygonVertex(j, 3);
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
	}
	return mesh;
};
