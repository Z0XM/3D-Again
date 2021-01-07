#include "Math3D.hpp"
#include <iostream>

float dot(Matrix A, Matrix B)
{
	return det(A * trans(B));
}

Matrix cross(Matrix A, Matrix B)
{
	Matrix mat(1, 3);
	Matrix mini(2, 2);

	mini[0][0] = A[0][1]; mini[0][1] = A[0][2];
	mini[1][0] = B[0][1]; mini[1][1] = B[0][2];
	mat[0][0] = det(mini);

	mini[0][0] = A[0][0]; mini[0][1] = A[0][2];
	mini[1][0] = B[0][0]; mini[1][1] = B[0][2];
	mat[0][1] = -det(mini);

	mini[0][0] = A[0][0]; mini[0][1] = A[0][1];
	mini[1][0] = B[0][0]; mini[1][1] = B[0][1];
	mat[0][2] = det(mini);

	return mat;

}
float crossMag(Matrix A, Matrix B)
{
	float cross = 0;
	Matrix mini(2, 2);

	mini[0][0] = A[0][1]; mini[0][1] = A[0][2];
	mini[1][0] = B[0][1]; mini[1][1] = B[0][2];
	cross += det(mini);

	mini[0][0] = A[0][0]; mini[0][1] = A[0][2];
	mini[1][0] = B[0][0]; mini[1][1] = B[0][2];
	cross += -det(mini);

	mini[0][0] = A[0][0]; mini[0][1] = A[0][1];
	mini[1][0] = B[0][0]; mini[1][1] = B[0][1];
	cross += det(mini);

	return cross;

}

Line::Line():
	a(1, 3), b(1, 3)
{
}

Line::Line(Matrix a, Matrix b):
	a(a), b(b - a)
{
}

Matrix Line::point(float K)
{
	return a + K * b;
}

Line::~Line()
{
}

Plane::Plane()
	:p(1, 3), n(1, 3)
{
}

Plane::Plane(Matrix p, Matrix n)
	: p(p), n(n)
{
}

Plane::Plane(Matrix a, Matrix b, Matrix c)
	: p(a), n(cross(a - b, c - b))
{
}

Plane::~Plane()
{
}

Matrix intersectionLinePlane(Line line, Plane plane)
{
	return  line.point(dot(plane.p - line.a, plane.n) / dot(line.b, plane.n));;
}