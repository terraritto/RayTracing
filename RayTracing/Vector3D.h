#pragma once

class Vector3D
{
public:
	double mPosX, mPosY, mPosZ;

	Vector3D();
	Vector3D(double a);
	Vector3D(double x, double y, double z);
	Vector3D(const Vector3D& v);
	Vector3D(const class Normal& n);
	Vector3D(const class Point3D& p);
	~Vector3D();
	Vector3D& operator=(const Vector3D& rhs);
	Vector3D& operator=(const class Normal& rhs);
	Vector3D& operator=(const class Point3D& rhs);

	Vector3D operator-() const;
	Vector3D operator*(const double a) const;
	Vector3D operator/(const double a) const;
	Vector3D operator+(const Vector3D& v) const;
	Vector3D& operator+=(const Vector3D& v);
	Vector3D operator-(const Vector3D& v) const;
	double operator*(const Vector3D& b) const;
	Vector3D operator^(const Vector3D& v) const;

	double LengthSq();
	double Length();
	void Normalize();
	Vector3D& hat();
};

Vector3D operator*(const double a, const Vector3D& v);