#include "FbxMesh.h"

#include <sstream>
#include "boost\thread\mutex.hpp"
#include "boost\thread.hpp"
#include "..\..\structs\VertexAddCallable.h"

using namespace shield;
using namespace shield::services;

std::vector<structs::Vertex>* FbxMesh::getVertexes()
{
	return &_vertexes;
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
void FbxMesh::normalize(
	float max,
	const structs::Vector3& min,
	const structs::Vector3& center
)
{
	for ( std::vector<structs::Vertex>::iterator vertex = _vertexes.begin();
		vertex != _vertexes.end();
		++vertex )
	{
		vertex->pos.x = (vertex->pos.x + min.dx + center.dx)/max;
		vertex->pos.y = (vertex->pos.y + min.dy + center.dx)/max;
		vertex->pos.z = (vertex->pos.z + min.dz + center.dx)/max;
	}
};
FbxMesh& FbxMesh::operator+=( const structs::Vector3& p )
{
	//int threadsNum = log( _vertexes.size() );
	boost::thread* threads = new boost::thread[THREADS_NUM];
	for ( int i = 0; i < THREADS_NUM; ++i )
	{
		structs::VertexAddCallable vadd(
			_vertexes,
			p,
			i,
			THREADS_NUM
		);
		threads[i] = boost::thread( vadd );
	}
	//delete threads;

	return *this;
};
