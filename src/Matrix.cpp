#include "Matrix.hpp"

Matrix::Matrix(int rows, int cols):
	data(new float* [rows]), rows(rows), cols(cols)
{
	for (int i = 0; i < rows; i++) 
	{
		data[i] = new float[cols];
		for (int j = 0; j < cols; j++)
			data[i][j] = 0;
	}
}

Matrix::Matrix(float** mat, int rows, int cols):
	data(new float* [rows]), rows(rows), cols(cols)
{
	for (int i = 0; i < rows; i++)
	{
		data[i] = new float[cols];
		for (int j = 0; j < cols; j++)
			data[i][j] = mat[i][j];
	}
}

Matrix::Matrix(const Matrix& A)
	:data(new float*[A.rows]), rows(A.rows), cols(A.cols)
{
	for (int i = 0; i < rows; i++)
	{
		data[i] = new float[cols];
		for (int j = 0; j < cols; j++)
			data[i][j] = A.data[i][j];
	}
}


Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)delete data[i];
	delete data;
}

float* Matrix::Matrix::operator[](int i)
{
	return data[i];
}

void Matrix::setData(float** mat)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			data[i][j] = mat[i][j];
}

Matrix operator+(Matrix A, Matrix B)
{
	Matrix R(A.rows, A.cols);
	
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.cols; j++) {
			R[i][j] = A[i][j] + B[i][j];
		}
	}
	return R;
}

Matrix operator-(Matrix A, Matrix B)
{
	Matrix R(A.rows, A.cols);

	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.cols; j++) {
			R[i][j] = A[i][j] - B[i][j];
		}
	}
	return R;
}

Matrix operator*(Matrix A, Matrix B)
{
	Matrix R(A.rows, B.cols);

	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < B.cols; j++) {
			float sum = 0;
			for(int k = 0; k < A.cols; k++)
				sum += A[i][k] * B[k][j];
			R[i][j] = sum;
		}
	}
	return R;
}

Matrix operator*(float n, Matrix A)
{
	Matrix R(A.rows, A.cols);

	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.cols; j++) {
			R[i][j] = A[i][j] * n;
		}
	}
	return R;
}

std::ostream& operator<<(std::ostream& out, Matrix& A)
{	
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.cols; j++) {
			out << A[i][j] << " ";
		}
		out << "\n";
	}
	out << "\n";
	return out;
}

Matrix trans(Matrix A)
{
	Matrix R(A.cols, A.rows);

	for (int i = 0; i < A.cols; i++) {
		for (int j = 0; j < A.rows; j++) {
			R[i][j] = A.data[j][i];
		}
	}

	return R;
}

float det(Matrix A)
{
	if (A.cols == 1 && A.rows == 1)return A[0][0];
	if (A.cols == 2 && A.rows == 2)return A[0][0] * A[1][1] - A[1][0] * A[0][1];

	float result = 0;

	float** miniMat = new float*[A.rows - 1];
	for (int i = 0; i < A.rows - 1; i++)miniMat[i] = new float[A.cols - 1];

	for (int k = 0; k < A.cols; k++) {
		for (int i = 1; i < A.rows; i++) {
			int c = 0;
			for (int j = 0; j < A.cols; j++) {
				if (j == k)continue;
				miniMat[i - 1][c] = A[i][j];
				c++;
			}
		}
		result += A[0][k] * det(Matrix(miniMat, A.rows - 1, A.cols - 1));
	}

	return result;
}

void generateMat1x3(Matrix& A, float x, float y, float z)
{
	A[0][0] = x;
	A[0][1] = y;
	A[0][2] = z;
}

void generateMat1x4(Matrix& A, float x, float y, float z, float w)
{
	A[0][0] = x;
	A[0][1] = y;
	A[0][2] = z;
	A[0][3] = w;
}