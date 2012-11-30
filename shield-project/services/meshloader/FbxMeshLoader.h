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
	};
};
};

#endif
