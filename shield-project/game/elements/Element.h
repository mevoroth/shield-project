#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <Windows.h>
#include "..\..\structs\Point.h"
#include "..\..\services\meshloader\Mesh.h"

using namespace shield::services;

namespace shield {
namespace game {
	class Element {
	public:
		Element( float, float, float );
		Element( const structs::Point& );
		Element( const Element& );
		~Element();
		void spawn( void );
		void refresh( void );
		unsigned long long getCurrentTime( void ) const;
		unsigned long long getSpawnTime( void ) const;
		const structs::Point& getPosition( void ) const;

		virtual bool hit( const Element& ) const = 0;
		virtual const Mesh* getMesh() const = 0;

	private:
		structs::Point _position;
		unsigned long long _spawnTime;
		unsigned long long _currentTime;
	};
};
};

#endif
