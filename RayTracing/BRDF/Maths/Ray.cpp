#include "Ray.h"

Ray::Ray()
	: mOrigin(0.0)
	, mDirection(0.0, 0.0, 1.0)
{

}

Ray::Ray(const Point3D& origin, const Vector3D& dir)
	: mOrigin(origin)
	, mDirection(dir)
{

}

Ray::Ray(const Ray& ray)
	: mOrigin(ray.mOrigin)
	, mDirection(ray.mDirection)
{

}

Ray& Ray::operator=(const Ray& rhs)
{
	if (this == &rhs)
	{
		return (*this);
	}

	mOrigin = rhs.mOrigin;
	mDirection = rhs.mDirection;

	return (*this);
}

Ray::~Ray()
{

}