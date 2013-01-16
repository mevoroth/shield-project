#ifndef _FBXMESH_H_
#define _FBXMESH_H_

#include <vector>
#include "Mesh.h"
#include "boost\interprocess\shared_memory_object.hpp"
#include "boost\interprocess\mapped_region.hpp"

using namespace boost::interprocess;

namespace shield {
namespace services {
	class FbxMesh : public Mesh
	{
	public:
		std::vector<structs::Vertex>* getVertexes();
		const wchar_t* getTexture() const;
		//const std::vector<int>& getIndices() const;
		//void putVertex( const structs::Vertex& );
		void putTriangle(
			const structs::Vertex&,
			const structs::Vertex&,
			const structs::Vertex&
		);
		void setTexture( wchar_t* );
		FbxMesh& operator+=( const structs::Vector3& );
		void normalize(
			float,
			const structs::Vector3&,
			const structs::Vector3&
		);

	private:
		enum
		{
			THREADS_NUM = 8
		};
		//std::vector<int> _indices;
		std::vector<structs::Vertex> _vertexes;
		wchar_t* _texture;
	};
};
};

#endif
