#include "FbxMeshLoader.h"
#include "FbxMesh.h"

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
const Mesh& FbxMeshLoader::load( const std::string& filename )
{
	FbxScene* scene = FbxScene::Create( _sdkManager, "scene" );
	FbxMesh mesh = FbxMesh();

	_importer->Initialize(
		filename.c_str(),
		-1,
		_sdkManager->GetIOSettings()
	);
	_importer->Import(scene);
	for ( int i = 0, c = scene->GetNodeCount(); i < c; ++i )
	{
		FbxNode* node = scene->GetNode(i);/*->GetNodeAttribute()->GetAttributeType();*/
		if (node->GetNodeAttribute()->GetAttributeType()
			== FbxNodeAttribute::eMesh)
		{
			fbxsdk_2013_3::FbxMesh* fbxmesh = (fbxsdk_2013_3::FbxMesh*)node;
			FbxVector4* vertexes = fbxmesh->GetControlPoints();
			int vertexesCount = fbxmesh->GetControlPointsCount();

			for ( int i = 0; i < vertexesCount; ++i )
			{
				// Vertex
			}

			int polygonCount = fbxmesh->GetPolygonCount();
			for ( int i = 0; i < polygonCount; ++i )
			{
				//int polygonSize = fbxmesh->GetPolygonSize( i );
				mesh.putTriangle(
					fbxmesh->GetPolygonVertex(i, 0),
					fbxmesh->GetPolygonVertex(i, 1),
					fbxmesh->GetPolygonVertex(i, 2)
				);
			}
		}
	}
	return mesh;
};
