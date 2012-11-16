#include "FbxMesh.h"

using namespace shield;
using namespace shield::services;

const std::vector<structs::Vertex>& FbxMesh::getVertexes() const
{
	return _vertexes;
};
const std::vector<int>& FbxMesh::getIndices() const
{
	return _indices;
};
void FbxMesh::putVertex( const structs::Vertex& v )
{
	_vertexes.push_back( v );
};
void FbxMesh::putTriangle( int v1, int v2, int v3 )
{
	_indices.push_back( v1 );
	_indices.push_back( v2 );
	_indices.push_back( v3 );
};
