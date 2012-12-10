#ifndef _IMESHLOADER_H_
#define _IMESHLOADER_H_

#include <string>
#include "Mesh.h"

namespace shield {
namespace services {
	class IMeshLoader
	{
	public:
		virtual const std::vector<Mesh*>& load( const std::string& ) = 0;
	};
};
};

#endif
