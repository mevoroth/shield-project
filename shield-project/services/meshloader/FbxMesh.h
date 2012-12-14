#ifndef _FBXMESH_H_
#define _FBXMESH_H_

#include <vector>
#include "Mesh.h"

namespace shield {
namespace services {
	class FbxMesh : public Mesh
	{
	public:
		std::vector<structs::Vertex> getVertexes() const;
		std::string getTexture() const;
		//const std::vector<int>& getIndices() const;
		//void putVertex( const structs::Vertex& );
		void putTriangle(
			const structs::Vertex&,
			const structs::Vertex&,
			const structs::Vertex&
		);
		void setTexture( const std::string& );
		FbxMesh& operator+=( const structs::Vector3& );

	private:
		//std::vector<int> _indices;
		std::vector<structs::Vertex> _vertexes;
		std::string _texture;
	};
};
};

#endif
