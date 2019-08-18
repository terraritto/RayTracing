#pragma once
#include "Point3D.h"
#include "Vector3D.h"

class Ray {
public:
	Point3D mOrigin;
	Vector3D mDirection;

	Ray();
	Ray(const Point3D& origin, const Vector3D& dir);
	Ray(const Ray& ray);

	Ray& operator=(const Ray& rhs);

	~Ray(void);
};