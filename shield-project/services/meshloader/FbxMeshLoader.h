#ifndef _FBXMESHLOADER_H_
#define _FBXMESHLOADER_H_

#define FBXSDK_NEW_API

#include <fbxsdk.h>
#include <fbxsdk\fileio\fbxiosettings.h>
#include "IMeshLoader.h"

namespace shield {
namespace services {
	class FbxMeshLoader : public IMeshLoader
	{
	public:
		FbxMeshLoader();
		~FbxMeshLoader();
		const std::vector<Mesh*>& load( const std::string& );
	private:
		FbxManager* _sdkManager;
		FbxImporter* _importer;

		/**
		 * @param[in] Mesh
		 * @param[in] Index
		 * @param[out] Normal
		 */
		void _getNormal(
			const fbxsdk_2013_3::FbxMesh*,
			int,
			DirectX::XMFLOAT3&
		) const;
		/**
		 * @param[in] Mesh
		 * @param[in] Polygon
		 * @param[in] Vertex
		 * @param[out] UV
		 */
		void FbxMeshLoader::_getUV(
			fbxsdk_2013_3::FbxMesh*,
			int,
			int,
			FbxVector2&
		) const;
		/**
		 * @param[in] Vertex position
		 * @param[in] Normal
		 * @param[in] Vertex index
		 * @param[in] UV
		 * @param[out] Vertex
		 */
		void _createVertex(
			const FbxVector4*,
			const DirectX::XMFLOAT3*,
			int,
			const FbxVector2&,
			structs::Vertex&
		) const;
	};
};
};

#endif
