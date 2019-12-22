#pragma once
#include <array>

class Matrix
{
public:
	Matrix();
	Matrix(const Matrix& mat);
	~Matrix();

	Matrix& operator=(const Matrix& rhs);
	Matrix operator*(const Matrix& mat) const;
	Matrix operator/(const double d);

	void SetIdentity();
public:
	std::array<std::array<double, 4>, 4> mMatrix;
};