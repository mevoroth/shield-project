#include "FbxMesh.h"

using namespace shield;
using namespace shield::services;

std::vector<structs::Vertex> FbxMesh::getVertexes() const
{
	return _vertexes;
};
/*const std::vector<int>& FbxMesh::getIndices() const
{
	return _indices;
};
void FbxMesh::putVertex( const structs::Vertex& v )
{
	_vertexes.push_back( v );
};*/
void FbxMesh::putTriangle(
	const structs::Vertex& v1,
	const structs::Vertex& v2,
	const structs::Vertex& v3
)
{
	_vertexes.push_back( v1 );
	_vertexes.push_back( v2 );
	_vertexes.push_back( v3 );
};
std::string FbxMesh::getTexture() const
{
	return _texture;
};
void FbxMesh::setTexture( const std::string& texture )
{
	_texture = texture;
};
FbxMesh& FbxMesh::operator+=( const structs::Vector3& p )
{
	for ( std::vector<structs::Vertex>::iterator it = _vertexes.begin();
		it != _vertexes.end();
		++it )
	{
		it->pos.x += p.dx;
		it->pos.y += p.dy;
		it->pos.z += p.dz;
	}
	return *this;
};
