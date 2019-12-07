#pragma once
#include "Vector3D.h"
class Vector3D;

class Point3D
{
public:
	double mPosX, mPosY, mPosZ;

	Point3D();
	Point3D(const double a);
	Point3D(const double a, const double b, const double c);
	Point3D(const Point3D& p);
	~Point3D();
	Point3D& operator=(const Point3D& p);

	Point3D operator-() const;
	class Vector3D operator-(const Point3D& p) const;
	Point3D operator+(const Vector3D& v) const;
	Point3D operator-(const Vector3D& v) const;
	Point3D operator*(const double a) const;
	double LengthSq(const Point3D& p) const;
	double Length(const Point3D& p) const;
};

Point3D operator*(double a, const Point3D& p);
Point3D operator-(const Point3D& p, double a);
Point3D operator+(const Point3D& p, double a);