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
		const Mesh* load( const std::string& );
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
			DirectX::XMFLOAT3*
		) const;
	};
};
};

#endif
