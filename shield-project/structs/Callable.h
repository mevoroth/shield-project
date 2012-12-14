#ifndef _CALLABLE_H_
#define _CALLABLE_H_

namespace shield {
namespace structs {
	class Callable
	{
	public:
		virtual void operator()() = 0;
	};
};
};

#endif
