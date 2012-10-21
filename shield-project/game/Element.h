#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "..\structs\Point.h"

namespace shield {
namespace game {
	class Element {
	public:
		Element( float, float, float );
		Element( structs::Point* );
		Element( const Element& );
		~Element();
		void spawn( double );
		void refresh( double );
		double getCurrentTime() const;
		double getSpawnTime() const;
		const structs::Point* getSpawn();

		virtual bool hit( const structs::Point* ) const = 0;

	private:
		structs::Point* _spawn;
		double _spawnTime;
		double _currentTime;
	};
};
};

#endif
