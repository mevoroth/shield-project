#ifndef _EVENTSMANAGER_H_
#define _EVENTSMANAGER_H_

#include "..\..\patterns\Observable.h"
#include "EventsState.h"
#include "GameAction.h"
#include "HopeAction.h"

using namespace shield::patterns;

namespace shield {
namespace services {
	class EventsManager :
		public Observable<EventsState, GameAction>,
		public Observable<EventsState, HopeAction>
	{
	public:
		using Observable<EventsState, GameAction>::bind;
		using Observable<EventsState, HopeAction>::bind;
		using Observable<EventsState, GameAction>::notify;
		using Observable<EventsState, HopeAction>::notify;
	};
};
};

#endif
