#pragma once
#include "GeometricObject.h"

class OpenCylinder : public GeometricObject
{
public:
	OpenCylinder();
	OpenCylinder(const double bottom, const double top, const double radius);
	OpenCylinder(const OpenCylinder& c);
	~OpenCylinder();
	OpenCylinder& operator=(const OpenCylinder& rhs);

	std::shared_ptr<OpenCylinder> Clone() const;

	bool hit(const Ray& ray, double& tMin, ShadeRec& sr) override;
	bool Shadow_hit(const Ray& ray, float& tMin) const override;
protected:
	double mY0, mY1;
	double mRadius;
};