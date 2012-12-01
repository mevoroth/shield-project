#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <DirectXMath.h>
#include "Point.h"

namespace shield {
namespace structs {
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 norm;
		//DirectX::XMFLOAT2 tex;
	};
};
};

#endif
