#include "Normal.h"
#include "Vector3D.h"
#include "Point3D.h"
#include <cmath>

Normal::Normal()
	: mPosX(0.0)
	, mPosY(0.0)
	, mPosZ(0.0)
{

}

Normal::Normal(double a)
	: mPosX(a)
	, mPosY(a)
	, mPosZ(a)
{

}

Normal::Normal(double x, double y, double z)
	: mPosX(x)
	, mPosY(y)
	, mPosZ(z)
{

}

Normal::Normal(const Normal& n)
	: mPosX(n.mPosX)
	, mPosY(n.mPosY)
	, mPosZ(n.mPosZ)
{

}

Normal::Normal(const Vector3D& v)
	: mPosX(v.mPosX)
	, mPosY(v.mPosY)
	, mPosZ(v.mPosZ)
{

}

Normal::~Normal()
{

}

Normal& Normal::operator=(const Normal& rhs)
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

Normal& Normal::operator=(const Vector3D& rhs)
{
	mPosX = rhs.mPosX;
	mPosY = rhs.mPosY;
	mPosZ = rhs.mPosZ;

	return (*this);
}

Normal& Normal::operator=(const Point3D& rhs)
{
	mPosX = rhs.mPosX;
	mPosY = rhs.mPosY;
	mPosZ = rhs.mPosZ;

	return (*this);
}

Normal Normal::operator-() const
{
	return (Normal(-mPosX,-mPosY,-mPosZ));
}

Normal Normal::operator+(const Normal& n) const
{
	return (Normal(mPosX + n.mPosX, mPosY + n.mPosY, mPosZ + n.mPosZ));
}

Normal& Normal::operator+=(const Normal& n)
{
	mPosX += n.mPosX;
	mPosY += n.mPosY;
	mPosZ += n.mPosZ;

	return (*this);
}


//dot product
double Normal::operator*(const Vector3D& v) const
{
	return (mPosX * v.mPosX + mPosY * v.mPosY + mPosZ * mPosZ);
}

Normal Normal::operator*(const double a) const
{
	return (Normal(mPosX * a, mPosY * a, mPosZ * a));
}

void Normal::Normalize()
{
	double length = std::sqrt(mPosX * mPosX + mPosY * mPosY + mPosZ * mPosZ);
	mPosX /= length; mPosY /= length; mPosZ /= length;
}

Normal operator*(const double a, const Normal& n)
{
	return (Normal(a * n.mPosX, a * n.mPosY, a * n.mPosZ));
}

Vector3D operator+(const Vector3D& v, const Normal& n)
{
	return (Vector3D(v.mPosX + n.mPosX, v.mPosY + n.mPosY, v.mPosZ + n.mPosZ));
}

Vector3D operator-(const Vector3D& v, const Normal& n) 
{
	return (Vector3D(v.mPosX - n.mPosX, v.mPosY - n.mPosY, v.mPosZ - n.mPosZ));
}

double operator*(const Vector3D& v, const Normal& n)
{
	return(v.mPosX * n.mPosX + v.mPosY * n.mPosY + v.mPosZ * n.mPosZ);
}