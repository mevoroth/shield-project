#ifndef _SETTINGS_H_
#define _SETTINGS_H_

namespace shield {
namespace settings {
	namespace weapons {
		const int LASER_BEAM_LV0 = 1;
		const int LASER_BEAM_LV1 = 3;
		const int LASER_BEAM_LV2 = 5;
		const int LASER_BEAM_LVMAX = 10;
	};
	namespace player {
		const int BASE_LIFE = 3;
	};
	namespace game {
		const int WIDTH = 5;
		const int HEIGHT = 5;
	};
	namespace system {
		const char WINDOW[] = "Shield";
		const int WIDTH = 1024;
		const int HEIGHT = 768;
		const float RATIO = (float)WIDTH/HEIGHT;
	};
};
};

#endif
