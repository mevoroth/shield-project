#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "..\..\structs\Vertex.h"
#include "..\..\structs\Point.h"

namespace shield {
namespace services {
	class Mesh
	{
	public:
		virtual std::vector<structs::Vertex> getVertexes() const = 0;
		virtual const wchar_t* getTexture() const = 0;
		virtual Mesh& operator+=( const structs::Vector3& ) = 0;
		/*virtual const std::vector<int>& getIndices() const = 0;*/
	};
};
};

#endif
