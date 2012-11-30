#include "Service.h"

using namespace shield;

services::ISound* Service::_sound = 0;
services::IGraphics* Service::_graphics = 0;
services::IControls* Service::_controls = 0;
services::IMeshLoader* Service::_meshLoader = 0;

services::ISound* Service::getSound()
{
	if (_sound == 0)
	{
		throw "Sound module not set";
	}
	return _sound;
};
void Service::setSound( services::ISound* s )
{
	_sound = s;
};
services::IGraphics* Service::getGraphics()
{
	if (_graphics == 0)
	{
		throw "Graphics module not set";
	}
	return _graphics;
};
void Service::setGraphics( services::IGraphics* g )
{
	_graphics = g;
};
services::IControls* Service::getControls()
{
	if (_controls == 0)
	{
		throw "Controls module not set";
	}
	return _controls;
};
void Service::setControls( services::IControls* c )
{
	_controls = c;
};
services::IMeshLoader* Service::getMeshLoader()
{
	if (_meshLoader == 0)
	{
		throw "MeshLoader module not set";
	}
	return _meshLoader;
};
void Service::setMeshLoader( services::IMeshLoader* m )
{
	_meshLoader = m;
};
