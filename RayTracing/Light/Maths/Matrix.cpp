#include "Matrix.h"

Matrix::Matrix()
{
	for (auto& obj : mMatrix)
	{
		obj.fill(0);
	}
}

Matrix::Matrix(const Matrix& mat)
{
	mMatrix = mat.mMatrix;
}

Matrix::~Matrix()
{
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mMatrix = rhs.mMatrix;
	
	return *this;
}

Matrix Matrix::operator*(const Matrix& mat) const
{
	Matrix product;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			double sum = 0.0;

			for (int j = 0; j < 4; j++)
			{
				sum += mMatrix[x][j] * mat.mMatrix[j][y];
			}

			product.mMatrix[x][y] = sum;
		}
	}

	return product;
}

Matrix Matrix::operator/(const double d)
{
	for (auto& obj : mMatrix)
	{
		for (auto& value : obj)
		{
			value /= d;
		}

		return *this;
	}
}

void Matrix::SetIdentity()
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (x == y)
			{
				mMatrix[x][y] = 1.0;
			}
			else
			{
				mMatrix[x][y] = 0.0;
			}
		}
	}
}
