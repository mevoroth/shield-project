#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

#include <map>
#include "Observer.h"

using namespace std;

namespace shield {
namespace patterns {
	template<typename State, typename Action>
	class Observable
	{
	public:
		/**/
		void bind( const State&, const Action&, Observer<State, Action>* );
		void notify( const State&, const Action& );

	private:
		multimap<pair<State, Action>, Observer<State, Action>*> _observers;
	};
	template <typename State, typename Action>
	void Observable<State, Action>::bind(
		const State& state,
		const Action& action,
		Observer<State, Action>* observer
	)
	{
		_observers.insert(
			pair<pair<State, Action>, Observer<State, Action>*>(
				pair<State, Action>(state, action),
				observer
			)
		);
	};
	template <typename State, typename Action>
	void Observable<State, Action>::notify(
		const State& state,
		const Action& action
	)
	{
		pair<
			multimap<pair<State, Action>, Observer<State, Action>*>::iterator,
			multimap<pair<State, Action>, Observer<State, Action>*>::iterator
		> ret = _observers.equal_range(
			pair<State, Action>(state, action)
		);
		for ( multimap<
				pair<State, Action>,
				Observer<State, Action>*
			>::iterator it = ret.first;
			it != ret.second;
			++it )
		{
			it->second->update();
		}
	};
};
};

#endif
