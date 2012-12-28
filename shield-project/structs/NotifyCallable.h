#ifndef _NOTIFYCALLABLE_H_
#define _NOTIFYCALLABLE_H_

#include "..\patterns\Observer.h"
#include "Callable.h"

using namespace shield::patterns;

namespace shield {
namespace structs {
	template <typename Action>
	class NotifyCallable : public Callable
	{
	public:
		NotifyCallable( Observer<Action>*, const Action&, void* );
		void operator()( void );

	private:
		Observer<Action>* _observer;
		Action _action;
		void* _params;
	};
	template <typename Action>
	NotifyCallable<Action>::NotifyCallable(
		Observer<Action>* observer,
		const Action& action,
		void* params
	)
	{
		_observer = observer;
		_action = action;
		_params = params;
	};
	template <typename Action>
	void NotifyCallable<Action>::operator()( void )
	{
		_observer->update( _action, _params );
	};
};
};

#endif
