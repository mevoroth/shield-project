#include "Engine.h"
#include "Service.h"

#include "services\NullControls.h"

using namespace shield;

Engine::Engine()
{
	Service::setControls( new services::NullControls() );
};

void Engine::run()
{
};
