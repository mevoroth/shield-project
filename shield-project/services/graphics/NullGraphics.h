#ifndef _NULLGRAPHICS_H_
#define _NULLGRAPHICS_H_

#include "IGraphics.h"

namespace shield {
namespace services {
	class NullGraphics : public IGraphics
	{
	public:
		NullGraphics();
		void begin( void );
		void end( void );
		void draw( const Point[], int, const wchar_t*, void*, void*, void* );
		void setCamera(
			float, float, float,
			float, float, float,
			float, float, float
		);
		void setPerspective( float, float, float, float );
		void updateMatrix();
	};
};
};

#endif
