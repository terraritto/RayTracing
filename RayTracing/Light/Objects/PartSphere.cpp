#include "PartSphere.h"
#include "..\Maths\Constants.h"

PartSphere::PartSphere()
	: GeometricObject()
	, mCenter(0.0)
	, mRadius(1.0)
	, mPhiMin(0.0)
	, mPhiMax(TWO_PI)
	, mThetaMin(0.0)
	, mThetaMax(PI)
{
}

PartSphere::PartSphere(Point3D c, double r, double azimuth_min, double azimuth_max, double polar_min, double polar_max)
	: GeometricObject()
	, mCenter(c)
	, mRadius(r)
	, mPhiMin(azimuth_min * PI_ON_180)
	, mPhiMax(azimuth_max * PI_ON_180)
	, mThetaMin(polar_min * PI_ON_180)
	, mThetaMax(polar_max * PI_ON_180)
{
}

PartSphere::PartSphere(Point3D c, double r)
	: GeometricObject()
	, mCenter(c)
	, mRadius(r)
	, mPhiMin(0.0)
	, mPhiMax(TWO_PI)
	, mThetaMin(0.0)
	, mThetaMax(PI)
{
}

PartSphere::PartSphere(const PartSphere& ps)
	: GeometricObject(ps)
	, mCenter(ps.mCenter)
	, mRadius(ps.mRadius)
	, mPhiMin(ps.mPhiMin)
	, mPhiMax(ps.mPhiMax)
	, mThetaMin(ps.mThetaMin)
	, mThetaMax(ps.mThetaMax)
{
}

PartSphere::~PartSphere()
{
}

PartSphere& PartSphere::operator=(const PartSphere& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	GeometricObject::operator=(rhs);

	mCenter = rhs.mCenter;
	mRadius = rhs.mRadius;
	mPhiMin = rhs.mPhiMin;
	mPhiMax = rhs.mPhiMax;
	mThetaMin = rhs.mThetaMin;
	mThetaMax = rhs.mThetaMax;

	return *this;
}

std::shared_ptr<PartSphere> PartSphere::Clone() const
{
	return std::shared_ptr<PartSphere>();
}

bool PartSphere::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	double t;
	Vector3D temp = ray.mOrigin - mCenter;
	double a = ray.mDirection * ray.mDirection;
	double b = 2.0 * temp * ray.mDirection;
	double c = temp * temp - mRadius * mRadius;
	double disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
	{
		return false;
	}
	else
	{
		double e = std::sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;

		if (t > kEpsilon)
		{
			Vector3D hit = ray.mOrigin + t * ray.mDirection - mCenter;

			double phi = std::atan2(hit.mPosX, hit.mPosZ);
			if (phi < 0.0) {
				phi += TWO_PI;
			}

			//check radius
			if (
				hit.mPosY <= mRadius * std::cos(mThetaMin) &&
				hit.mPosY >= mRadius * std::cos(mThetaMax) &&
				phi >= mPhiMin && phi <= mPhiMax
				)
			{
				tMin = t;
				sr.mNormal = (temp + t * ray.mDirection) / mRadius;
				
				//check hit inside
				if (-ray.mDirection * sr.mNormal < 0.0)
				{
					sr.mNormal = -sr.mNormal;
				}
				
				sr.mLocalHitPoint = ray.mOrigin + tMin * ray.mDirection;
				return true;
			}
		}
		t = (-b + e) / denom;
		if (t > kEpsilon)
		{
			Vector3D hit = ray.mOrigin + t * ray.mDirection - mCenter;

			double phi = std::atan2(hit.mPosX, hit.mPosZ);
			if (phi < 0.0) {
				phi += TWO_PI;
			}

			if (
				hit.mPosY <= mRadius * std::cos(mThetaMin) &&
				hit.mPosY >= mRadius * std::cos(mThetaMax) &&
				phi >= mPhiMin && phi <= mPhiMax
				)
			{
				tMin = t;
				sr.mNormal = (temp + t * ray.mDirection) / mRadius;
				
				if (-ray.mDirection * sr.mNormal < 0.0)
				{
					sr.mNormal = -sr.mNormal;
				}
				
				sr.mLocalHitPoint = ray.mOrigin + tMin * ray.mDirection;
				return true;
			}
		}
	}

	return false;
}

bool PartSphere::Shadow_hit(const Ray& ray, float& tmin) const
{
	double t;
	Vector3D temp = ray.mOrigin - mCenter;
	double a = ray.mDirection * ray.mDirection;
	double b = 2.0 * temp * ray.mDirection;
	double c = temp * temp - mRadius * mRadius;
	double disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
	{
		return false;
	}
	else
	{
		double e = std::sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;

		if (t > kEpsilon)
		{
			Vector3D hit = ray.mOrigin + t * ray.mDirection - mCenter;

			double phi = std::atan2(hit.mPosX, hit.mPosZ);
			if (phi < 0.0) {
				phi += TWO_PI;
			}

			if (
				hit.mPosY <= mRadius * std::cos(mThetaMin) &&
				hit.mPosY >= mRadius * std::cos(mThetaMax) &&
				phi >= mPhiMin && phi <= mPhiMax
				)
			{
				tmin = t;
				return true;
			}
		}
		t = (-b + e) / denom;
		if (t > kEpsilon)
		{
			Vector3D hit = ray.mOrigin + t * ray.mDirection - mCenter;

			double phi = std::atan2(hit.mPosX, hit.mPosZ);
			if (phi < 0.0) {
				phi += TWO_PI;
			}

			if (
				hit.mPosY <= mRadius * std::cos(mThetaMin) &&
				hit.mPosY >= mRadius * std::cos(mThetaMax) &&
				phi >= mPhiMin && phi <= mPhiMax
				)
			{
				tmin = t;
				return true;
			}
		}
	}

	return false;
}

void PartSphere::SetPhi(const double min, const double max)
{
	mPhiMin = min;
	mPhiMax = max;
}

void PartSphere::SetTheta(const double min, const double max)
{
	mThetaMin = min;
	mThetaMax = max;
}
