#ifndef _FBXMESH_H_
#define _FBXMESH_H_

#include <vector>
#include "Mesh.h"

namespace shield {
namespace services {
	class FbxMesh : public Mesh
	{
	public:
		const std::vector<structs::Vertex>& getVertexes() const;
		const std::vector<int>& getIndices() const;
		void putVertex( const structs::Vertex& );
		void putTriangle( int, int, int );

	private:
		std::vector<int> _indices;
		std::vector<structs::Vertex> _vertexes;
	};
};
};

#endif
