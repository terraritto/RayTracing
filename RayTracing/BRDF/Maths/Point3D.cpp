#include <cmath>
#include "Point3D.h"

Point3D::Point3D()
	: mPosX(0)
	, mPosY(0)
	, mPosZ(0)
{

}

Point3D::Point3D(const double a)
	: mPosX(a)
	, mPosY(a)
	, mPosZ(a)
{

}

Point3D::Point3D(const double a, const double b, const double c)
	: mPosX(a)
	, mPosY(b)
	, mPosZ(c)
{

}

Point3D::Point3D(const Point3D& p)
	: mPosX(p.mPosX)
	, mPosY(p.mPosY)
	, mPosZ(p.mPosZ)
{

}

Point3D::~Point3D()
{

}

Point3D& Point3D::operator=(const Point3D& rhs)
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

Point3D Point3D::operator-() const
{
	return (Point3D(-mPosX, -mPosY, -mPosZ));
}

Vector3D Point3D::operator-(const Point3D& p) const
{
	return (Vector3D(mPosX - p.mPosX, mPosY - p.mPosY, mPosZ - p.mPosZ));
}

Point3D Point3D::operator+(const Vector3D& v) const
{
	return (Point3D(mPosX + v.mPosX, mPosY + v.mPosY, mPosZ + v.mPosZ));
}

Point3D Point3D::operator-(const Vector3D& v) const
{
	return (Point3D(mPosX - v.mPosX, mPosY - v.mPosY, mPosZ - v.mPosZ));
}

Point3D Point3D::operator*(const double a) const 
{
	return (Point3D(mPosX * a, mPosY * a, mPosZ * a));
}

double Point3D::LengthSq(const Point3D& p) const
{
	return (std::pow(mPosX - p.mPosX, 2) + std::pow(mPosY - p.mPosY, 2) + std::pow(mPosZ - p.mPosZ,2));
}

double Point3D::Length(const Point3D& p) const
{
	return (std::sqrt(LengthSq(p)));
}

//non-member
Point3D operator*(double a, const Point3D& p)
{
	return (Point3D(a * p.mPosX, a * p.mPosY, a * p.mPosZ));
}