#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

#include <map>
#include <boost\thread.hpp>
#include "Observer.h"
#include "..\structs\NotifyCallable.h"

using namespace std;

namespace shield {
namespace patterns {
	template<typename Action>
	class Observable
	{
	public:
		/**/
		void bind( const Action&, Observer<Action>* );
		void notify( const Action&, void* );

	private:
		multimap<Action, Observer<Action>*> _observers;
	};
	template <typename Action>
	void Observable<Action>::bind(
		const Action& action,
		Observer<Action>* observer
	)
	{
		_observers.insert(
			pair<Action, Observer<Action>*>(
				action,
				observer
			)
		);
	};
	template <typename Action>
	void Observable<Action>::notify( const Action& action, void* params )
	{
		pair<
			multimap<Action, Observer<Action>*>::iterator,
			multimap<Action, Observer<Action>*>::iterator
		> ret = _observers.equal_range( action );
		for ( multimap<Action, Observer<Action>*>::iterator it =
				ret.first;
			it != ret.second;
			++it )
		{
			NotifyCallable<Action> callable( it->second, action, params );
			boost::thread th( callable );
			//it->second->update( action, params );
		}
	};
};
};

#endif
