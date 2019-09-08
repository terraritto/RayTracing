#include "Sphere.h"
#include <cmath>

const double Sphere::kEpsilon = 0.001;

Sphere::Sphere()
	: GeometricObject()
	, mCenter(0.0)
	, mRadius(1.0)
{

}

Sphere::Sphere(Point3D c, double r)
	: GeometricObject()
	, mCenter(c)
	, mRadius(r)
{

}

Sphere::Sphere(const Sphere& sphere)
	: GeometricObject(sphere)
	, mCenter(sphere.mCenter)
	, mRadius(sphere.mRadius)
{

}

Sphere& Sphere::operator=(const Sphere& rhs)
{
	if (this == &rhs)
	{
		return (*this);
	}

	GeometricObject::operator=(rhs);
	mCenter = rhs.mCenter;
	mRadius = rhs.mRadius;

	return (*this);
}

Sphere::~Sphere()
{

}

std::shared_ptr<Sphere> Sphere::Clone() const
{
	return std::make_shared<Sphere>((*this));
}

void Sphere::SetCenter(const Point3D& c)
{
	mCenter = c;
}

void Sphere::SetCenter(const double x, const double y, const double z)
{
	mCenter.mPosX = x;
	mCenter.mPosY = y;
	mCenter.mPosZ = z;
}

void Sphere::SetRadius(const double r)
{
	mRadius = r;
}

bool Sphere::hit(const Ray& ray, double& tMin, ShadeRec& sr) const
{
	double t;
	Vector3D temp = ray.mOrigin - mCenter; //direction vector for Sphere. (o - c) 
	double a = ray.mDirection * ray.mDirection; // a = d * d
	double b = 2.0 * temp * ray.mDirection; // b = 2(o - c) * d
	double c = temp * temp - mRadius * mRadius; // c = (o - c) * (o - c) - r * r;
	double disc = b * b - 4.0 * a * c; // discriminant

	if (disc < 0.0) // No hit
	{
		return false;
	}
	else // one or two hit
	{
		double e = std::sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;  //swaller root

		if (t > kEpsilon)
		{
			tMin = t;
			sr.mNormal = (temp + t * ray.mDirection) / mRadius; 
			sr.mLocalHitPoint = ray.mOrigin + t * ray.mDirection;
			return true;
		}

		t = (-b + e) / denom; //larger root
		if (t > kEpsilon)
		{
			tMin = t;
			sr.mNormal = (temp + t * ray.mOrigin) / mRadius;
			sr.mLocalHitPoint = ray.mOrigin + t * ray.mDirection;
			return true;
		}
	}
	return false;
}