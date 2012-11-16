#include <iostream>
#include "NullGraphics.h"

using namespace shield;

services::NullGraphics::NullGraphics()
{
	std::cout << "NullGraphics initialized" << std::endl;
};
void services::NullGraphics::draw( const Point vertexes[], int size )
{
	std::cout << "Drawing ..." << std::endl;
};
