#include "Engine.h"
#include "Service.h"

#include "services\NullControls.h"
#include "services\NullGraphics.h"
#include "services\NullSound.h"

using namespace shield;

Engine::Engine()
{
	Service::setControls( new services::NullControls() );
	Service::setGraphics( new services::NullGraphics() );
	Service::setSound( new services::NullSound() );
};

void Engine::run()
{
	// Load menu
};
