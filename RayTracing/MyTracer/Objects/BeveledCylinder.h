#pragma once
#include "Compound.h"

class BeveledCylinder : public Compound
{
public:
	BeveledCylinder(const double bottom, const double top, const double radius, const double beveled_radius);
	BeveledCylinder(const BeveledCylinder& cc);
	~BeveledCylinder();
	BeveledCylinder& operator=(const BeveledCylinder& rhs);

	std::shared_ptr<BeveledCylinder> Clone() const;

	bool hit(const Ray& ray, double& tMin, ShadeRec& sr) override;
	bool Shadow_hit(const Ray& ray, float& tMin) const override;
private:
	BBox mBbox;
};