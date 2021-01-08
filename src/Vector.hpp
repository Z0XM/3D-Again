#pragma once
#include <ostream>

class Vector {
public:
	float x, y, z;

	Vector();
	Vector(float x, float y, float z);
	~Vector();

	void setData(float x, float y, float z);
};

Vector operator+(Vector, Vector);
Vector operator-(Vector, Vector);
Vector operator*(float, Vector);
std::ostream& operator<<(std::ostream&, Vector);

float mag(Vector);