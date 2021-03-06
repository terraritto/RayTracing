#include "BBox.h"
#include "../Maths/Constants.h"

BBox::BBox(Point3D p0, Point3D p1)
	: mP0(p0)
	, mP1(p1)
{
}

BBox::BBox(const BBox& bbox)
	: mP0(bbox.mP0)
	, mP1(bbox.mP1)
{
}

std::shared_ptr<BBox> BBox::Clone() const
{
	return std::make_shared<BBox>(*this);
}

BBox& BBox::operator=(const BBox& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mP0 = rhs.mP0;
	mP1 = rhs.mP1;

	return *this;
}

BBox::~BBox()
{
}

bool BBox::hit(const Ray& ray) const
{
	Point3D origin(ray.mOrigin);
	Point3D dir(ray.mDirection.mPosX, ray.mDirection.mPosY, ray.mDirection.mPosZ);
	Point3D tMin;
	Point3D tMax;

	double a = 1.0 / dir.mPosX;
	if (a >= 0)
	{
		tMin.mPosX = (mP0.mPosX - origin.mPosX) * a;
		tMax.mPosX = (mP1.mPosX - origin.mPosX) * a;
	}
	else
	{
		tMin.mPosX = (mP1.mPosX - origin.mPosX) * a;
		tMax.mPosX = (mP0.mPosX - origin.mPosX) * a;
	}

	double b = 1.0 / dir.mPosY;
	if (b >= 0)
	{
		tMin.mPosY = (mP0.mPosY - origin.mPosY) * b;
		tMax.mPosY = (mP1.mPosY - origin.mPosY) * b;
	}
	else
	{
		tMin.mPosY = (mP1.mPosY - origin.mPosY) * b;
		tMax.mPosY = (mP0.mPosY - origin.mPosY) * b;
	}

	double c = 1.0 / dir.mPosZ;
	if (c >= 0)
	{
		tMin.mPosZ = (mP0.mPosZ - origin.mPosZ) * c;
		tMax.mPosZ = (mP1.mPosZ - origin.mPosZ) * c;
	}
	else
	{
		tMin.mPosZ = (mP1.mPosZ - origin.mPosZ) * c;
		tMax.mPosZ = (mP0.mPosZ - origin.mPosZ) * c;
	}

	double t0, t1;
	//finding largest t
	if (tMin.mPosX > tMin.mPosY)
	{
		t0 = tMin.mPosX;
	}
	else
	{
		t0 = tMin.mPosY;
	}

	if (tMin.mPosZ > t0)
	{
		t0 = tMin.mPosZ;
	}

	//finding smallest
	if (tMax.mPosX < tMax.mPosY)
	{
		t1 = tMax.mPosX;
	}
	else
	{
		t1 = tMax.mPosY;
	}

	if (tMax.mPosZ < t1)
	{
		t1 = tMax.mPosZ;
	}

	return (t0 < t1 && t1 > kEpsilon);
}

bool BBox::Inside(const Point3D& p) const
{
	return (p.mPosX > mP0.mPosX&& p.mPosX < mP1.mPosX) &&
		(p.mPosY > mP0.mPosY&& p.mPosY < mP1.mPosY) &&
		(p.mPosZ > mP1.mPosZ&& p.mPosZ < mP1.mPosZ);
}
