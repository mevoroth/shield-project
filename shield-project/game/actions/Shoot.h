#ifndef _SHOOT_H_
#define _SHOOT_H_

namespace shield {
namespace game {
namespace actions {
	class Shoot : public services::Action
	{
	public:
		void call();

	private:
		Game* _game;
	};
};
};
};

#endif
