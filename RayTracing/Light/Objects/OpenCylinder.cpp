#include "OpenCylinder.h"

OpenCylinder::OpenCylinder()
	: GeometricObject()
	, mY0(-1.0)
	, mY1(1.0)
	, mRadius(1.0)
{
}

OpenCylinder::OpenCylinder(const double bottom, const double top, const double radius)
	: GeometricObject()
	, mY0(bottom)
	, mY1(top)
	, mRadius(radius)
{
}

OpenCylinder::OpenCylinder(const OpenCylinder& c)
	: GeometricObject(c)
	, mY0(c.mY0)
	, mY1(c.mY1)
	, mRadius(c.mRadius)
{
}

OpenCylinder::~OpenCylinder()
{
}

OpenCylinder& OpenCylinder::operator=(const OpenCylinder& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	GeometricObject::operator=(rhs);

	mY0 = rhs.mY0;
	mY1 = rhs.mY1;
	mRadius = rhs.mRadius;

	return *this;
}

std::shared_ptr<OpenCylinder> OpenCylinder::Clone() const
{
	return std::make_shared<OpenCylinder>(*this);
}

bool OpenCylinder::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	double t;
	double ox = ray.mOrigin.mPosX; double oy = ray.mOrigin.mPosY; double oz = ray.mOrigin.mPosZ;
	double dx = ray.mDirection.mPosX; double dy = ray.mDirection.mPosY; double dz = ray.mDirection.mPosZ;

	double a = dx * dx + dz * dz;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - mRadius * mRadius;
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
			double yHit = oy + t * dy;

			if (yHit > mY0 && yHit < mY1)
			{
				tMin = t;
				sr.mNormal = (Normal((ox + t * dx) / mRadius, 0.0, (oz + t * dz) / mRadius));

				// hit from inside
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
			double yHit = oy + t * dy;

			if (yHit > mY0 && yHit < mY1)
			{
				tMin = t;
				sr.mNormal = Normal((ox + t * dx) / mRadius, 0.0, (oz + t * dz) / mRadius);

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

bool OpenCylinder::Shadow_hit(const Ray& ray, float& tMin) const
{
	double t;
	double ox = ray.mOrigin.mPosX; double oy = ray.mOrigin.mPosY; double oz = ray.mOrigin.mPosZ;
	double dx = ray.mDirection.mPosX; double dy = ray.mDirection.mPosY; double dz = ray.mDirection.mPosZ;

	double a = dx * dx + dy * dy;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - mRadius * mRadius;
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
			double yHit = oy + t * dy;

			if (yHit > mY0&& yHit < mY1)
			{
				tMin = t;
				return true;
			}
		}

		t = (-b + e) / denom;

		if (t > kEpsilon)
		{
			double yHit = oy + t * dy;

			if (yHit > mY0 && yHit < mY1)
			{
				tMin = t;
				return true;
			}
		}
	}

	return false;
}