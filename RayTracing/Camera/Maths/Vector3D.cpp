#include <cmath>
#include "Vector3D.h"
#include "Normal.h"
#include "Point3D.h"

Vector3D::Vector3D()
	: mPosX(0.0)
	, mPosY(0.0)
	, mPosZ(0.0)
{

}

Vector3D::Vector3D(double a)
	: mPosX(a)
	, mPosY(a)
	, mPosZ(a)
{

}

Vector3D::Vector3D(double x, double y, double z)
	: mPosX(x)
	, mPosY(y)
	, mPosZ(z)
{

}

Vector3D::Vector3D(const Vector3D& vec)
	: mPosX(vec.mPosX)
	, mPosY(vec.mPosY)
	, mPosZ(vec.mPosZ)
{

}

Vector3D::Vector3D(const Normal& n)
	: mPosX(n.mPosX)
	, mPosY(n.mPosY)
	, mPosZ(n.mPosZ)
{

}

Vector3D::Vector3D(const Point3D& p)
	: mPosX(p.mPosX)
	, mPosY(p.mPosY)
	, mPosZ(p.mPosZ)
{

}

Vector3D::~Vector3D()
{

}

Vector3D& Vector3D::operator=(const Vector3D& rhs)
{
	if (this == &rhs)
	{
		return (*this);
	}

	mPosX = rhs.mPosX;
	mPosY = rhs.mPosY;
	mPosZ = rhs.mPosZ;

	return (*this);
}

Vector3D& Vector3D::operator=(const Normal& rhs)
{
	mPosX = rhs.mPosX;
	mPosY = rhs.mPosY;
	mPosZ = rhs.mPosZ;
	return (*this);
}

Vector3D& Vector3D::operator=(const Point3D& rhs)
{
	mPosX = rhs.mPosX;
	mPosY = rhs.mPosY;
	mPosZ = rhs.mPosZ;
	return (*this);
}

Vector3D Vector3D::operator-() const
{
	return (Vector3D(-mPosX, -mPosY, -mPosZ));
}

Vector3D Vector3D::operator*(const double a) const
{
	return (Vector3D(mPosX * a, mPosY * a, mPosZ * a));
}

Vector3D Vector3D::operator/(const double a) const
{
	return (Vector3D(mPosX / a, mPosY / a, mPosZ / a));
}

Vector3D Vector3D::operator+(const Vector3D& v) const
{
	return (Vector3D(mPosX + v.mPosX, mPosY + v.mPosY, mPosZ + v.mPosZ));
}

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
	mPosX += v.mPosX;
	mPosY += v.mPosY;
	mPosZ += v.mPosZ;
	return (*this);
}

Vector3D Vector3D::operator-(const Vector3D& v) const
{
	return (Vector3D(mPosX - v.mPosX, mPosY - v.mPosY, mPosZ - v.mPosZ));
}

double Vector3D::operator*(const Vector3D& v) const
{
	return (mPosX * v.mPosX + mPosY * v.mPosY + mPosZ * v.mPosZ);
}

Vector3D Vector3D::operator^(const Vector3D& v) const
{
	return (Vector3D(mPosY * v.mPosZ - mPosZ * v.mPosY, mPosZ * v.mPosX - mPosX * v.mPosZ, mPosX * v.mPosY - mPosY * v.mPosX));
}

double Vector3D::LengthSq()
{
	return (std::pow(mPosX,2) + std::pow(mPosY,2) + std::pow(mPosZ,2));
}

double Vector3D::Length(void)
{
	return std::sqrt(LengthSq());
}

void Vector3D::Normalize()
{
	double length = Length();
	mPosX /= length; mPosY /= length; mPosZ /= length;
}

Vector3D& Vector3D::hat()
{
	double length = Length();
	mPosX /= length; mPosY /= length; mPosZ /= length;
	return (*this);
}

//non-member
Vector3D operator*(const double a, const Vector3D& v)
{
	return (Vector3D(a * v.mPosX, a * v.mPosY, a * v.mPosZ));
}