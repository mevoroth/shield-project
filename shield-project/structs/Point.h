#ifndef _POINT_H_
#define _POINT_H_

#include "..\patterns\Cloneable.h"
#include "Vector3.h"

namespace shield {
namespace structs {
	class Point : public shield::patterns::Cloneable<Point>
	{
	public:
		Point( float, float, float );
		Point( const Point& );
		Point clone() const;
		float x;
		float y;
		float z;
		Point operator+( const Vector3& ) const;
		Point& operator+=( const Vector3& );
	};
};
};

#endif
