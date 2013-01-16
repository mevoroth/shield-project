#include "VertexAddCallable.h"

using namespace shield::structs;

VertexAddCallable::VertexAddCallable(
	std::vector<Vertex>& vertexes,
	const Vector3& v,
	int it,
	int threadsNum
)
	: _it( it ),
	_v( v ),
	_vertexes( vertexes ),
	_threadsNum( threadsNum ),
	_jump( threadsNum*BLOCK )
{
};
void VertexAddCallable::operator()( void )
{
	int size = _vertexes.size();
	for ( int it = _it*BLOCK; it < size; it += _jump )
	{
		for ( int i = 0; i < BLOCK && i+it < size; ++i )
		{
			DirectX::XMFLOAT3& pos = _vertexes[i+it].pos;
			pos.x += _v.dx;
			pos.y += _v.dy;
			pos.z += _v.dz;
		}
	}
	/*int* it = (int*)_it.get_address();
	(*_mutex)->lock();
	int i = *it;
	++*it;
	(*_mutex)->unlock();

	while ( i < size )
	{
		DirectX::XMFLOAT3& pos = _vertexes[i].pos;
		pos.x += _v.dx;
		pos.y += _v.dy;
		pos.z += _v.dz;
		(*_mutex)->lock();
		i = *it;
		++*it;
		(*_mutex)->unlock();
	}*/
};
