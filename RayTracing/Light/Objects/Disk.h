#pragma once
#include "GeometricObject.h"

class Disk : public GeometricObject
{
public:
	Disk(Point3D center, Normal normal, float rad);
	Disk(const Disk& disk);
	Disk& operator=(const Disk& rhs);

	std::shared_ptr<Disk> Clone() const;
	bool hit(const Ray& ray, double& tMin, ShadeRec& sr) override;
	bool Shadow_hit(const Ray& ray, float& tMin) const override;

	void SetCenter(const Point3D center);
	Point3D GetCenter() const;
	void SetRadius(const float radius);
	float GetRadius() const;
	void SetNormal(const Normal normal);
	Normal GetNormal() const;
protected:
	Point3D mCenter;
	Normal mNormal;
	float mRadius;
};