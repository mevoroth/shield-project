#ifndef _POINT_H_
#define _POINT_H_

#include "..\patterns\Cloneable.h"

namespace shield {
namespace structs {
	class Point : public shield::patterns::Cloneable<Point>
	{
	public:
		Point( float, float, float );
		Point& clone() const;
		float x;
		float y;
		float z;
	};
};
};

#endif
