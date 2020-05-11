#pragma once
#include "Compound.h"

class SolidCylinder : public Compound
{
public:
	SolidCylinder();
	SolidCylinder(const double bottom, const double top, const double radius);
	SolidCylinder(const SolidCylinder& cc);
	~SolidCylinder();
	SolidCylinder& operator=(const SolidCylinder& rhs);
	
	std::shared_ptr<SolidCylinder> Clone() const;

	bool hit(const Ray& ray, double& tMin, ShadeRec& sr) override;
	bool Shadow_hit(const Ray& ray, float& tMin) const override;
private:
	BBox mBbox;
};