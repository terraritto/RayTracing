#pragma once
#include "GeometricObject.h"

class SmoothTriangle : public GeometricObject
{
public:
	Normal mN0, mN1, mN2; //normal at each vertex

	SmoothTriangle();
	SmoothTriangle(const Point3D& a, const Point3D& b, const Point3D& c);
	SmoothTriangle(const SmoothTriangle& st);
	~SmoothTriangle();
	SmoothTriangle& operator=(const SmoothTriangle& rhs);

	std::shared_ptr<SmoothTriangle> Clone() const;
	
	virtual bool hit(const Ray& ray, double& tMin, ShadeRec& s);
	bool Shadow_hit(const Ray& ray, float& tMin) const override;
	BBox GetBoundingBox() const override;
private:
	Point3D mV0, mV1, mV2;

	Normal InterpolateNormal(const float beta, const float gamma) const;
};