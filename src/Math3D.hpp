#pragma once
#include "Vector.hpp"

Vector unit(Vector);
float dot(Vector, Vector);
Vector cross(Vector, Vector);
float crossMag(Vector, Vector);

class Line {
public:
	Vector a, b;
	Line();
	Line(Vector a, Vector b);
	Vector point(float K);
	~Line();
};

class Plane {
public:
	Vector p, n;
	Plane();
	Plane(Vector p, Vector n);
	Plane(Vector a, Vector b, Vector c);
	~Plane();
};

Vector intersectionLinePlane(Line, Plane);