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
const wchar_t* FbxMesh::getTexture() const
{
	return _texture;
};
void FbxMesh::setTexture( wchar_t* texture )
{
	_texture = texture;
};
void FbxMesh::normalize( float max, const structs::Point& min )
{
	for ( std::vector<structs::Vertex>::iterator vertex = _vertexes.begin();
		vertex != _vertexes.end();
		++vertex )
	{
		vertex->pos.x = (vertex->pos.x + min.x)/(max*2.5f);
		vertex->pos.y = (vertex->pos.y + min.y)/(max*2.5f);
		vertex->pos.z = (vertex->pos.z + min.z)/(max*2.5f);
	}
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
