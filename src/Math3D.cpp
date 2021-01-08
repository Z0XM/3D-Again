#include "Math3D.hpp"
#include <iostream>

Vector unit(Vector v)
{
	float m = mag(v);
	return Vector(v.x / m, v.y / m, v.z / m);
}

float dot(Vector u, Vector v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector cross(Vector u, Vector v)
{
	return Vector(u.y * v.z - u.z * v.y, v.x * u.z - u.x * v.z, u.x * v.y - u.y * v.x);

}
float crossMag(Vector u, Vector v)
{

	return mag(cross(u, v));
}

Line::Line()
{
}

Line::Line(Vector a, Vector b):
	a(a), b(b - a)
{
}

Vector Line::point(float K)
{
	return a + K * b;
}

Line::~Line()
{
}

Plane::Plane()
{
}

Plane::Plane(Vector p, Vector n)
	: p(p), n(n)
{
}

Plane::Plane(Vector a, Vector b, Vector c)
	: p(a), n(unit(cross(a - b, c - b)))
{
}

Plane::~Plane()
{
}

Vector intersectionLinePlane(Line line, Plane plane)
{
	//std::cout << plane.p - line.a << plane.n << "\n";
	return  line.point(dot(plane.p - line.a, plane.n) / dot(line.b, plane.n));;
}