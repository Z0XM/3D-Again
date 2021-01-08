#include "Vector.hpp"

Vector::Vector()
	:x(0), y(0), z(0)
{
}

Vector::Vector(float x, float y, float z)
	:x(x), y(y), z(z)
{
}

Vector::~Vector()
{
}

void Vector::setData(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector operator+(Vector u, Vector v)
{
	return Vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector operator-(Vector u, Vector v)
{
	return Vector(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vector operator*(float n, Vector v)
{
	return Vector(n * v.x, n * v.y, n * v.z);
}

std::ostream& operator<<(std::ostream& out, Vector v)
{
	out << "( " << v.x << ", " << v.y << ", " << v.z << " )";
	return out;
}

float mag(Vector v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
