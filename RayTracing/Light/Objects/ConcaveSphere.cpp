#include "ConcaveSphere.h"
#include <cmath>

const double ConcaveSphere::kEpsilon = 0.001;

ConcaveSphere::ConcaveSphere()
	: GeometricObject()
	, mCenter(0.0)
	, mRadius(1.0)
{
}

ConcaveSphere::ConcaveSphere(Point3D center, double r)
	: GeometricObject()
	, mCenter(center)
	, mRadius(r)
{
}

ConcaveSphere::ConcaveSphere(const ConcaveSphere& sphere)
	: GeometricObject(sphere)
	, mCenter(sphere.mCenter)
	, mRadius(sphere.mRadius)
{
}

ConcaveSphere& ConcaveSphere::operator=(const ConcaveSphere& rhs)
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

ConcaveSphere::~ConcaveSphere()
{
}

std::shared_ptr<ConcaveSphere> ConcaveSphere::Clone() const
{
	return std::make_shared<ConcaveSphere>(*this);
}

void ConcaveSphere::SetCenter(const Point3D& c)
{
	mCenter = c;
}

void ConcaveSphere::SetCenter(const double x, const double y, const double z)
{
	mCenter.mPosX = x;
	mCenter.mPosY = y;
	mCenter.mPosZ = z;
}

void ConcaveSphere::SetRadius(const double r)
{
	mRadius = r;
}

bool ConcaveSphere::hit(const Ray& ray, double& tMin, ShadeRec& sr)
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
			sr.mNormal = -(temp + t * ray.mDirection) / mRadius;
			sr.mLocalHitPoint = ray.mOrigin + t * ray.mDirection;
			return true;
		}

		t = (-b + e) / denom; //larger root
		if (t > kEpsilon)
		{
			tMin = t;
			sr.mNormal = -(temp + t * ray.mDirection) / mRadius;
			sr.mLocalHitPoint = ray.mOrigin + t * ray.mDirection;
			return true;
		}
	}
	return false;
}

bool ConcaveSphere::Shadow_hit(const Ray& ray, float& tMin) const
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
			return true;
		}

		t = (-b + e) / denom; //larger root
		if (t > kEpsilon)
		{
			tMin = t;
			return true;
		}
	}
	return false;
}
