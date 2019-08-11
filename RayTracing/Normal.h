#pragma once
#include "Vector3D.h"
#include "Point3D.h"
class Vector3D;
class Point3D;

class Normal
{
public:
	double mPosX, mPosY, mPosZ;
	
	Normal();
	Normal(double a);
	Normal(double x, double y, double z);
	Normal(const Normal& n);
	Normal(const Vector3D& v);
	~Normal();
	Normal& operator=(const Normal& rhs);
	Normal& operator=(const Vector3D& rhs);
	Normal& operator=(const Point3D& rhs);

	Normal operator-() const;
	Normal operator+(const Normal& n) const;
	Normal& operator+=(const Normal& n);
	double operator*(const Vector3D& v) const;
	Normal operator*(const double a) const;

	void Normalize();
};

Normal operator*(const double a, const Normal& n);
class Vector3D operator+(const Vector3D& v, const Normal& n);
class Vector3D operator-(const Vector3D& v, const Normal& n);
double operator*(const Vector3D& v, const Normal& n);