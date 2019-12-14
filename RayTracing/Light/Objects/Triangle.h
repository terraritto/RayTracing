#pragma once
#include "GeometricObject.h"
#include "../Utility/ShadeRec.h"
#include "../Maths/Ray.h"

class Triangle : public GeometricObject
{
public:
	Triangle();
	Triangle(const Point3D& a, const Point3D& b, const Point3D& c);
	Triangle(const Triangle& triangle);
	Triangle& operator=(const Triangle& rhs);
	std::shared_ptr<Triangle> Clone() const;

	virtual bool hit(const Ray& ray, double& tMin, ShadeRec& s);
	bool Shadow_hit(const Ray& ray, float& tMin) const override;
	BBox GetBoundingBox() const override;
public:
	Point3D mV0, mV1, mV2;
	Normal mNormal;
};