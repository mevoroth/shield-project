#ifndef _EVENTSMANAGER_H_
#define _EVENTSMANAGER_H_

#include "..\..\patterns\Observable.h"
#include "GameAction.h"
#include "HopeAction.h"
#include "EnemyAction.h"
#include "BulletAction.h"

using namespace shield::patterns;

namespace shield {
namespace services {
	class EventsManager :
		public Observable<GameAction>,
		public Observable<HopeAction>,
		public Observable<EnemyAction>,
		public Observable<BulletAction>
	{
	public:
		using Observable<GameAction>::bind;
		using Observable<HopeAction>::bind;
		using Observable<EnemyAction>::bind;
		using Observable<BulletAction>::bind;
		using Observable<GameAction>::notify;
		using Observable<HopeAction>::notify;
		using Observable<EnemyAction>::notify;
		using Observable<BulletAction>::notify;
	};
};
};

#endif
