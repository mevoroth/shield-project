#include <iostream>
#include "NullGraphics.h"

using namespace shield;
using namespace std;

services::NullGraphics::NullGraphics()
{
	cout << "NullGraphics initialized" << endl;
};
void services::NullGraphics::begin( void )
{
	cout << "Begin draw ..." << endl;
};
void services::NullGraphics::end( void )
{
	cout << "End draw ..." << endl;
};
void services::NullGraphics::draw( const Point vertexes[], int vertexesSize,
								  const std::string& texture )
{
	cout << "Drawing ..." << endl;
};
void services::NullGraphics::setCamera(
	float eyeX, float eyeY, float eyeZ,
	float atX, float atY, float atZ,
	float upX, float upY, float upZ
)
{
	cout << "Setting camera ..." << endl;
	cout << "Eye : (" << eyeX << "," << eyeY << "," << eyeZ << ")" << endl;
	cout << "At : (" << atX << "," << atY << "," << atZ << ")" << endl;
	cout << "Up : (" << upX << "," << upY << "," << upZ << ")" << endl;
};
void services::NullGraphics::setPerspective( float fovAngleY, float ratio,
											float nearZ, float farZ )
{
	cout << "Setting perspective ..." << endl;
	cout << "Angle : " << fovAngleY << endl;
	cout << "Ratio : " << ratio << endl;
	cout << "NearZ : " << nearZ << endl;
	cout << "FarZ : " << farZ << endl;
};
