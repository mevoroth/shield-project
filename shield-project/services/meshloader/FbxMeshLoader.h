#ifndef _FBXMESHLOADER_H_
#define _FBXMESHLOADER_H_

#include "IMeshLoader.h"

namespace shield {
namespace services {
	class FbxMeshLoader : public IMeshLoader
	{
	public:
		const Mesh& load( const std::string& );
	};
};
};

#endif
