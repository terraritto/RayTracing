#pragma once
#include "GeometricObject.h"

class PartSphere :public GeometricObject
{
public:
	PartSphere();
	PartSphere(Point3D c, double r, double azimuth_min, double azimuth_max,
		double polar_min, double polar_max);
	PartSphere(Point3D c, double r);
	PartSphere(const PartSphere& ps);
	~PartSphere();
	PartSphere& operator=(const PartSphere& rhs);

	std::shared_ptr<PartSphere> Clone() const;

	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
	bool Shadow_hit(const Ray& ray, float& tmin) const override;

	void SetPhi(const double min, const double max);
	void SetTheta(const double min, const double max);
private:
	Point3D mCenter;
	double mRadius;
	double mPhiMin, mPhiMax;
	double mThetaMin, mThetaMax;
};