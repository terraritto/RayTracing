#include "Triangle.h"
#include <algorithm>

Triangle::Triangle()
	: GeometricObject()
	, mV0(0,0,0)
	, mV1(0,0,1)
	, mV2(1,0,0)
	, mNormal(0,1,0)
{
}

Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c)
	: GeometricObject()
	, mV0(a)
	, mV1(b)
	, mV2(c)
{
	mNormal = (mV1 - mV0) ^ (mV2 - mV0);
	mNormal.Normalize();
}

Triangle::Triangle(const Triangle& triangle)
	: GeometricObject(triangle)
	, mV0(triangle.mV0)
	, mV1(triangle.mV1)
	, mV2(triangle.mV2)
	, mNormal(triangle.mNormal)
{
}

Triangle& Triangle::operator=(const Triangle& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mV0 = rhs.mV0;
	mV1 = rhs.mV1;
	mV2 = rhs.mV2;
	mNormal = rhs.mNormal;
	return *this;
}

std::shared_ptr<Triangle> Triangle::Clone() const
{
	return std::make_shared<Triangle>(*this);
}

bool Triangle::hit(const Ray& ray, double& tMin, ShadeRec& sr) const
{
	double a = mV0.mPosX - mV1.mPosX, b = mV0.mPosX - mV2.mPosX;
	double c = ray.mDirection.mPosX, d = mV0.mPosX - ray.mOrigin.mPosX;
	double e = mV0.mPosY - mV1.mPosY, f = mV0.mPosY - mV2.mPosY;
	double g = ray.mDirection.mPosY, h = mV0.mPosY - ray.mOrigin.mPosY;
	double i = mV0.mPosZ - mV1.mPosZ, j = mV0.mPosZ - mV2.mPosZ;
	double k = ray.mDirection.mPosZ, l = mV0.mPosZ - ray.mOrigin.mPosZ;
	
	double m = f * k - g * j, n = h * k - g * l;
	double p = f * l - h * j, q = g * i - e * k;
	double s = e * j - f * i;

	double invDenom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;

	// first check
	if (beta < 0.0)
	{
		return false;
	}

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * invDenom;

	// second check
	if (gamma < 0.0)
	{
		return false;
	}

	// third check
	if (beta + gamma > 1.0)
	{
		return false;
	}

	double e3 = a * p - b * r + d * s;
	double t = e3 * invDenom;

	// final check
	if (t < kEpsilon)
	{
		return false;
	}

	//hit
	tMin = t;
	sr.mNormal = mNormal;
	sr.mLocalHitPoint = ray.mOrigin + t * ray.mDirection;

	return true;
}

bool Triangle::Shadow_hit(const Ray& ray, float& tMin) const
{
	double a = mV0.mPosX - mV1.mPosX, b = mV0.mPosX - mV2.mPosX;
	double c = ray.mDirection.mPosX, d = mV0.mPosX - ray.mOrigin.mPosX;
	double e = mV0.mPosY - mV1.mPosY, f = mV0.mPosY - mV2.mPosY;
	double g = ray.mDirection.mPosY, h = mV0.mPosY - ray.mOrigin.mPosY;
	double i = mV0.mPosZ - mV1.mPosZ, j = mV0.mPosZ - mV2.mPosZ;
	double k = ray.mDirection.mPosZ, l = mV0.mPosZ - ray.mOrigin.mPosZ;

	double m = f * k - g * j, n = h * k - g * l;
	double p = f * l - h * j, q = g * i - e * k;
	double s = e * j - f * i;

	double invDenom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;

	// first check
	if (beta < 0.0)
	{
		return false;
	}

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * invDenom;

	// second check
	if (gamma < 0.0)
	{
		return false;
	}

	// third check
	if (beta + gamma > 1.0)
	{
		return false;
	}

	double e3 = a * p - b * r + d * s;
	double t = e3 * invDenom;

	// final check
	if (t < kEpsilon)
	{
		return false;
	}

	//hit
	tMin = t;

	return true;
}

BBox Triangle::GetBoundingBox() const
{
	double delta = 0.00001;
	Point3D ansMin, ansMax;
	//p0
	ansMin.mPosX = std::min({ mV0.mPosX,mV1.mPosX,mV2.mPosX });
	ansMin.mPosY = std::min({ mV0.mPosY,mV1.mPosY,mV2.mPosY });
	ansMin.mPosZ = std::min({ mV0.mPosZ,mV1.mPosZ,mV2.mPosZ });
	//p1
	ansMax.mPosX = std::max({ mV0.mPosX,mV1.mPosX,mV2.mPosX });
	ansMax.mPosY = std::max({ mV0.mPosY,mV1.mPosY,mV2.mPosY });
	ansMax.mPosZ = std::max({ mV0.mPosZ,mV1.mPosZ,mV2.mPosZ });

	//minus or plus delta ,It means make BBox
	ansMin = ansMin - delta;
	ansMax = ansMax + delta;

	return BBox(ansMin, ansMax);
}
