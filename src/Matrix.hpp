#pragma once

#include <ostream>

class Matrix {
protected:
	float **data;
public:
	int rows, cols;

	Matrix(int rows, int cols);
	Matrix(float** mat, int rows, int cols);
	Matrix(const Matrix&);
	~Matrix();
	
	float* operator[](int i);

	void setData(float**);

	friend Matrix operator+(Matrix, Matrix);
	friend Matrix operator-(Matrix, Matrix);
	friend Matrix operator*(Matrix, Matrix);
	friend Matrix operator*(float, Matrix);
	friend std::ostream& operator<<(std::ostream&, Matrix&);

	friend Matrix trans(Matrix);
	friend float det(Matrix);
};

Matrix operator+(Matrix, Matrix);
Matrix operator-(Matrix, Matrix);
Matrix operator*(Matrix, Matrix);
Matrix operator*(float, Matrix);
std::ostream& operator<<(std::ostream&, Matrix&);

Matrix trans(Matrix);
float det(Matrix);

void generateMat1x3(Matrix&, float x, float y, float z);
void generateMat1x4(Matrix&, float x, float y, float z, float w);
