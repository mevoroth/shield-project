#ifndef _OBSERVER_H_
#define _OBSERVER_H_

namespace shield {
namespace patterns {
	template <typename Action>
	class Observer
	{
	public:
		virtual void update( const Action&, void* ) = 0;
	};
};
};

#endif
