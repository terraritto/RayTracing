#include "Box.h"

Box::Box(const Point3D& p0, const Point3D& p1)
	: GeometricObject()
	, mP0(p0)
	, mP1(p1)
{
}

Box::Box(const Box& box)
	: GeometricObject(box)
	, mP0(box.mP0)
	, mP1(box.mP1)
{
}

Box::~Box()
{
}

Box& Box::operator=(Box& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	GeometricObject::operator=(rhs);
	mP0 = rhs.mP0;
	mP1 = rhs.mP1;

	return *this;
}

std::shared_ptr<Box> Box::Clone() const
{
	return std::make_shared<Box>(*this);
}

bool Box::hit(const Ray& ray, double& t, ShadeRec& s)
{
	Point3D origin(ray.mOrigin);
	Point3D dir(ray.mDirection.mPosX,ray.mDirection.mPosY,ray.mDirection.mPosZ);
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
	int faceIn, faceOut;
	
	//find largest
	if (tMin.mPosX > tMin.mPosY)
	{
		t0 = tMin.mPosX;
		faceIn = (a >= 0.0) ? 0 : 3;
	}
	else
	{
		t0 = tMin.mPosY;
		faceIn = (b >= 0.0) ? 1 : 4;
	}
	if (tMin.mPosZ > t0)
	{
		t0 = tMin.mPosZ;
		faceIn = (c >= 0.0) ? 2 : 5;
	}

	//find smallest
	if (tMax.mPosX < tMax.mPosY)
	{
		t1 = tMax.mPosX;
		faceOut = (a >= 0.0) ? 3 : 0;
	}
	else
	{
		t1 = tMax.mPosY;
		faceOut = (b >= 0.0) ? 4 : 1;
	}
	if (tMax.mPosZ < t1)
	{
		t1 = tMax.mPosZ;
		faceOut = (c >= 0.0) ? 5 : 2;
	}

	if ((t0 < t1) && (t1 > kEpsilon))
	{
		if (t0 > kEpsilon)
		{
			t = t0;
			s.mNormal = GetNormal(faceIn);
		}
		else
		{
			t = t1;
			s.mNormal = GetNormal(faceOut);
		}

		s.mLocalHitPoint = ray.mOrigin + t * ray.mDirection;
		return true;
	}
	else
	{
		return false;
	}
}

bool Box::Shadow_hit(const Ray& ray, float& t) const
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
	int faceIn, faceOut;

	//find largest
	if (tMin.mPosX > tMin.mPosY)
	{
		t0 = tMin.mPosX;
		faceIn = (a >= 0.0) ? 0 : 3;
	}
	else
	{
		t0 = tMin.mPosY;
		faceIn = (b >= 0.0) ? 1 : 4;
	}
	if (tMin.mPosZ > t0)
	{
		t0 = tMin.mPosZ;
		faceIn = (c >= 0.0) ? 2 : 5;
	}

	//find smallest
	if (tMax.mPosX < tMax.mPosY)
	{
		t1 = tMax.mPosX;
		faceOut = (a >= 0.0) ? 3 : 0;
	}
	else
	{
		t1 = tMax.mPosY;
		faceOut = (b >= 0.0) ? 4 : 1;
	}
	if (tMax.mPosZ < t1)
	{
		t1 = tMax.mPosZ;
		faceOut = (c >= 0.0) ? 5 : 2;
	}

	if (t0 < t1 && t1 > kEpsilon)
	{
		if (t0 > kEpsilon)
		{
			t = t0;
		}
		else
		{
			t = t1;
		}
		return true;
	}
	else
	{
		return false;
	}
}

Normal Box::GetNormal(const int faceHit) const
{
	switch (faceHit)
	{
	case 0: return Normal(-1, 0, 0); //-x face
	case 1: return Normal(0, -1, 0); //-y face
	case 2: return Normal(0, 0, -1); //-z face
	case 3: return Normal(1, 0, 0);  //+x face
	case 4: return Normal(0, 1, 0);  //+y face
	case 5: return Normal(0, 0, 1);  //+z face
	}
}

void Box::SetP0(const Point3D p0)
{
	mP0 = p0;
}

Point3D Box::GetP0() const
{
	return mP0;
}

void Box::SetP1(const Point3D p1)
{
	mP1 = p1;
}

Point3D Box::GetP1() const
{
	return mP1;
}
