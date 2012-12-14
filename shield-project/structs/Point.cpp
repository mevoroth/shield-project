#include "Point.h"

using namespace shield::structs;

Point::Point( float x, float y, float z )
{
	this->x = x;
	this->y = y;
	this->z = z;
};
Point::Point( const Point& p )
{
	x = p.x;
	y = p.y;
	z = p.z;
};
Point Point::clone() const
{
	return Point(*this);
};
Point& Point::operator+( const Vector3& dir ) const
{
	Point* p = new Point(*this);
	p->x += dir.dx;
	p->y += dir.dy;
	p->z += dir.dz;

	return *p;
};
