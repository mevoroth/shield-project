#ifndef _NULLSOUND_H_
#define _NULLSOUND_H_

#include "ISound.h"

namespace shield {
namespace services {
	class NullSound : public ISound
	{
	public:
		NullSound();
	};
};
};

#endif
