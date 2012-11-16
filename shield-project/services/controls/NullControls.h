#ifndef _NULLCONTROLS_H_
#define _NULLCONTROLS_H_

#include "IControls.h"

namespace shield {
namespace services {
	class NullControls : public IControls
	{
	public:
		NullControls( void );
	};
};
};

#endif
