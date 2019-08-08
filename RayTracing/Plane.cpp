#include "Plane.h"
#include "Ray.h"
#include "ShadeRec.h"

const double Plane::kEpsilon = 0.001;

Plane::Plane()
	: GeometricObject()
	, mPoint(0.0)
	, mNormal(0, 1, 0)
{

}

Plane::Plane(const Point3D& point, const Normal& normal)
	: GeometricObject()
	, mPoint(point)
	, mNormal(normal)
{
	mNormal.Normalize(); //ê≥ãKâª
}

Plane::Plane(const Plane& plane)
	: GeometricObject()
	, mPoint(plane.mPoint)
	, mNormal(plane.mNormal)
{

}

std::shared_ptr<Plane> Plane::Clone() const
{
	return std::make_shared<Plane>(*this);
}

Plane& Plane::operator=(const Plane& rhs)
{
	if (this == &rhs)
	{
		return (*this);
	}

	//çXêV
	GeometricObject::operator=(rhs);
	mPoint = rhs.mPoint;
	mNormal = rhs.mNormal;

	return (*this);
}

Plane::~Plane()
{

}

bool Plane::hit(const Ray& ray, double& tMin, ShadeRec& sr) const
{
	double t = (mPoint - ray.mOrigin) * mNormal / (ray.mDirection * mNormal);

	if (t > kEpsilon)
	{
		tMin = t;
		sr.mNormal = mNormal;
		sr.mLocalHitPoint = ray.mOrigin + t * ray.mDirection;

		return (true);
	}
	else
	{
		return (false);
	}
}