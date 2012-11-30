#ifndef _NULLGRAPHICS_H_
#define _NULLGRAPHICS_H_

#include "IGraphics.h"

namespace shield {
namespace services {
	class NullGraphics : public IGraphics
	{
	public:
		NullGraphics();
		void draw( const Point[], int, const int[], int );
		void setCamera(
			float, float, float,
			float, float, float,
			float, float, float
		);
		void setPerspective( float, float, float, float );
	};
};
};

#endif
