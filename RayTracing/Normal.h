#pragma once

class Normal
{
public:
	double mPosX, mPosY, mPosZ;
	
	Normal();
	Normal(double a);
	Normal(double x, double y, double z);
	Normal(const Normal& n);
	Normal(const class Vector3D& v);
	~Normal();
	Normal& operator=(const Normal& rhs);
	Normal& operator=(const class Vector3D& rhs);
	Normal& operator=(const class Point3D& rhs);

	Normal operator-() const;
	Normal operator+(const Normal& n) const;
	Normal& operator+=(const Normal& n);
	double operator*(const class Vector3D& v) const;
	Normal operator*(const double a) const;

	void Normalize();
};

Normal operator*(const double a, const Normal& n);
class Vector3D operator+(const class Vector3D& v, const Normal& n);
class Vector3D operator-(const class Vector3D& v, const Normal& n);
double operator*(const class Vector3D& v, const Normal& n);