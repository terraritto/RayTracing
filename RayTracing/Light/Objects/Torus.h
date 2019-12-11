#pragma once

#include "GeometricObject.h"
#include "BBox.h"
#include <array>

class Torus : public GeometricObject
{
public:
	Torus(double a, double b);
	Torus(const Torus& torus);
	std::shared_ptr<Torus> Clone() const;
	Torus& operator=(Torus& rhs);

	bool hit(const Ray& ray, double& tMin, ShadeRec& sr) const override;
	bool Shadow_hit(const Ray& ray, float& tMin) const override;
private:
	double mA;
	double mB;
	Normal ComputeNormal(Point3D p) const;
};