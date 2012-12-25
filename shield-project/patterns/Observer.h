#ifndef _OBSERVER_H_
#define _OBSERVER_H_

namespace shield {
namespace patterns {
	template <typename State, typename Action>
	class Observer
	{
	public:
		virtual void update() = 0;
	};
};
};

#endif
