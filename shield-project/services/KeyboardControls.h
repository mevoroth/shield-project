#ifndef _DIRECTINPUTCONTROLS_H_
#define _DIRECTINPUTCONTROLS_H_

#include <Windows.h>
#include "IControls.h"

namespace shield {
namespace services {
	class KeyboardControls : public IControls
	{
	public:
		KeyboardControls( HINSTANCE );
	};
};
};

#endif
