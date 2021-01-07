#pragma once
#include "Matrix.hpp"

float dot(Matrix, Matrix);
Matrix cross(Matrix, Matrix);
float crossMag(Matrix, Matrix);

class Line {
public:
	Matrix a, b;
	Line();
	Line(Matrix a, Matrix b);
	Matrix point(float K);
	~Line();
};

class Plane {
public:
	Matrix p, n;
	Plane();
	Plane(Matrix p, Matrix n);
	Plane(Matrix a, Matrix b, Matrix c);
	~Plane();
};

Matrix intersectionLinePlane(Line, Plane);