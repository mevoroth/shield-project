#ifndef _VERTEXADDCALLABLE_H_
#define _VERTEXADDCALLABLE_H_

#include <vector>
#include "boost\interprocess\mapped_region.hpp"
#include "boost\thread\mutex.hpp"
#include "Callable.h"
#include "Vector3.h"
#include "Vertex.h"

using namespace boost::interprocess;

namespace shield {
namespace structs {
	class VertexAddCallable : public Callable
	{
	public:
		VertexAddCallable(
			std::vector<Vertex>&,
			const Vector3&,
			int,
			int
		);
		void operator()( void );
	private:
		enum
		{
			BLOCK = 256
		};
		std::vector<Vertex>& _vertexes;
		Vector3 _v;
		int _it;
		int _jump;
		int _threadsNum;
	};
};
};

#endif
