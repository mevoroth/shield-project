#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "services\sound\ISound.h"
#include "services\controls\IControls.h"
#include "services\graphics\IGraphics.h"

namespace shield
{
	class Service
	{
	public:
		/**
		 * @return ISound& Sound module
		 */
		static services::ISound* getSound();
		/**
		 * Set sound module
		 * @param Sound module
		 */
		static void setSound( services::ISound* );
		static services::IGraphics* getGraphics();
		/**
		 * Set graphic module
		 * @param Graphic module
		 */
		static void setGraphics( services::IGraphics* );
		static services::IControls* getControls();
		static void setControls( services::IControls* );

	private:
		static services::ISound* _sound;
		static services::IGraphics* _graphics;
		static services::IControls* _controls;

	};
};

#endif
