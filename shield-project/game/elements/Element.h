#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <Windows.h>
#include <vector>
#include "..\..\structs\Point.h"
#include "..\..\structs\Vector3.h"
#include "..\..\services\meshloader\Mesh.h"

using namespace shield::patterns;
using namespace shield::services;

namespace shield {
namespace game {
	class Element
	{
	public:
		Element(
			float, float, float,
			const structs::Vector3&,
			const std::vector<Mesh*>&
		);
		Element(
			const structs::Point&,
			const structs::Vector3&,
			const std::vector<Mesh*>&
		);
		Element( const Element& );
		~Element();
		structs::Point getPosition( void ) const;
		structs::Vector3 getDirection( void ) const;
		std::vector<Mesh*>* getMesh();
		
		virtual void update( LONGLONG );
		virtual bool isVisible( const structs::Point& );
		virtual bool hit( const Element& ) = 0;
		virtual bool isDead() const = 0;

	protected:
		void _moveTo( const structs::Point& );

	private:
		structs::Point _position;
		structs::Vector3 _direction;
		std::vector<Mesh*> _meshes;
	};
};
};

#endif
