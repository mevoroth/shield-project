#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "..\..\structs\Vertex.h"

namespace shield {
namespace services {
	class Mesh
	{
	public:
		virtual const std::vector<structs::Vertex>& getVertexes() const = 0;
		virtual const std::string& getTexture() const = 0;
		/*virtual const std::vector<int>& getIndices() const = 0;*/
	};
};
};

#endif
