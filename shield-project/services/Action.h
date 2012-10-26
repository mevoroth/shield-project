#ifndef _ACTION_H_
#define _ACTION_H_

namespace shield {
namespace services {
	class Action
	{
	public:
		virtual void call() = 0;
	};
};
};

#endif
