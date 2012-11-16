#ifndef _IGRAPHICS_H_
#define _IGRAPHICS_H_

#include "..\..\structs\Point.h"
#include "..\..\structs\Vertex.h"

using namespace shield::structs;

namespace shield {
namespace services {
	class IGraphics
	{
	public:
		virtual void draw( const Vertex[], int ) = 0;
	};
};
};

#endif
