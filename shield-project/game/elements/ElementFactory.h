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
			int,
			int
		);
		static Element* getArchangel(
			const structs::Point&,
			int,
			int
		);
		static Element* getRuler(
			const structs::Point&,
			int,
			int
		);
		static Element* getAuthority(
			const structs::Point&,
			int,
			int
		);
		static Element* getVirtue(
			const structs::Point&,
			int,
			int
		);
		static Element* getDominion(
			const structs::Point&,
			int,
			int
		);
		static Element* getThrone(
			const structs::Point&,
			int,
			int
		);
		static Element* getCherub(
			const structs::Point&,
			int,
			int
		);
		static Element* getSeraph(
			const structs::Point&,
			int,
			int
		);
	};
};
};

#endif
