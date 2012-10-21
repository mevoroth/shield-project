#ifndef _NULLGRAPHICS_H_
#define _NULLGRAPHICS_H_

#include "IGraphics.h"

namespace shield {
namespace services {
	class NullGraphics : public IGraphics
	{
	public:
		NullGraphics();
	};
};
};

#endif
