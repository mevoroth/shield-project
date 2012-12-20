#ifndef _ELEMENTFACTORY_H_
#define _ELEMENTFACTORY_H_

#include "Element.h"

namespace shield {
namespace game {
	class ElementFactory
	{
	public:
		static Element* getAngel(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int
		);
		static Element* getArchangel(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int
		);
		static Element* getRuler(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int
		);
		static Element* getAuthority(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int
		);
		static Element* getVirtue(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int
		);
		static Element* getDominion(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int
		);
		static Element* getThrone(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int
		);
		static Element* getCherub(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int
		);
		static Element* getSeraph(
			const structs::Point&,
			const structs::Vector3&,
			int,
			int
		);
	};
};
};

#endif
