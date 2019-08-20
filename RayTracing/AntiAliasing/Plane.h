#pragma once
#include "GeometricObject.h"
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "ShadeRec.h"
#include <memory>

class Plane : public GeometricObject
{
public:
	Plane();
	Plane(const Point3D& point, const Normal& normal);
	Plane(const Plane& plane);
	Plane& operator=(const Plane& rhs);
	virtual ~Plane();

	virtual std::shared_ptr<Plane> Clone() const;
	virtual bool hit(const Ray& ray, double& tMin,ShadeRec& sr) const;
private:
	Point3D mPoint;
	Normal mNormal;

	static const double kEpsilon;
};