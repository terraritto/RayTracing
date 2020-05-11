#include "Disk.h"

Disk::Disk(Point3D center, Normal normal, float rad)
	: GeometricObject()
	, mCenter(center)
	, mNormal(normal)
	, mRadius(rad)
{
	mNormal.Normalize();
}

Disk::Disk(const Disk& disk)
	: GeometricObject(disk)
	, mCenter(disk.mCenter)
	, mNormal(disk.mNormal)
	, mRadius(disk.mRadius)
{
	mNormal.Normalize();
}

Disk& Disk::operator=(const Disk& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	GeometricObject::operator=(rhs);
	mCenter = rhs.mCenter;
	mNormal = rhs.mNormal;
	mNormal.Normalize();
	mRadius = rhs.mRadius;
	return *this;
}

std::shared_ptr<Disk> Disk::Clone() const
{
	return std::make_shared<Disk>(*this);
}

bool Disk::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	float t = (mCenter - ray.mOrigin) * mNormal / (ray.mDirection * mNormal);
	
	if(t <= kEpsilon)
	{
		return false;
	}

	Point3D p = ray.mOrigin + t * ray.mDirection;
	
	if (mCenter.LengthSq(p) < (mRadius * mRadius))
	{
		tMin = t;
		sr.mNormal = mNormal;
		sr.mLocalHitPoint = p;
		return true;
	}
	return false;
}

bool Disk::Shadow_hit(const Ray& ray, float& tMin) const
{
	float t = (mCenter - ray.mOrigin) * mNormal / (ray.mDirection * mNormal);

	if (t <= kEpsilon)
	{
		return false;
	}

	Point3D p = ray.mOrigin + t * ray.mDirection;

	if (mCenter.LengthSq(p) < (mRadius * mRadius))
	{
		tMin = t;
		return true;
	}
	return false;
}

void Disk::SetCenter(const Point3D center)
{
	mCenter = center;
}

Point3D Disk::GetCenter() const
{
	return mCenter;
}

void Disk::SetRadius(const float radius)
{
	mRadius = radius;
}

float Disk::GetRadius() const
{
	return mRadius;
}

void Disk::SetNormal(const Normal normal)
{
	mNormal = normal;
}

Normal Disk::GetNormal() const
{
	return mNormal;
}
