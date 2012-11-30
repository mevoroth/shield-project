#ifndef _IGRAPHICS_H_
#define _IGRAPHICS_H_

#include "..\..\structs\Point.h"
#include "..\..\structs\Vertex.h"

using namespace shield::structs;

namespace shield {
namespace services {
	class IGraphics
	{
	public:
		virtual void draw( const Vertex[], int, const int[], int ) = 0;
		/**
		 * Look at
		 * @param[in] Eye X
		 * @param[in] Eye Y
		 * @param[in] Eye Z
		 * @param[in] At X
		 * @param[in] At Y
		 * @param[in] At Z
		 * @param[in] Up X
		 * @param[in] Up Y
		 * @param[in] Up Z
		 */
		virtual void setCamera(
			float, float, float,
			float, float, float,
			float, float, float
		) = 0;
		/**
		 * Perspective projection
		 * @param[in] Angle champ de vision
		 * @param[in] Ratio (16/9, 4/3, ...)
		 * @param[in] Position plan proche
		 * @param[in] Position plan �loign�
		 */
		virtual void setPerspective( float, float, float, float ) = 0;
	};
};
};

#endif