#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <Windows.h>

#include "..\structs\Point.h"

namespace shield {
namespace game {
	class Element {
	public:
		Element( float, float, float );
		Element( structs::Point* );
		Element( const Element& );
		~Element();
		void spawn( void );
		void refresh( void );
		unsigned long long getCurrentTime( void ) const;
		unsigned long long getSpawnTime( void ) const;
		const structs::Point* getSpawn( void ) const;

		virtual bool hit( const structs::Point* ) const = 0;

	private:
		structs::Point* _spawn;
		unsigned long long _spawnTime;
		unsigned long long _currentTime;
	};
};
};

#endif
