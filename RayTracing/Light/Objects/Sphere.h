#pragma once
#include "GeometricObject.h"
#include "../Maths/Point3D.h"
#include "../Utility/ShadeRec.h"
#include "../Maths/Ray.h"

class ShadeRec;

class Sphere : public GeometricObject
{
public:
	Sphere();
	Sphere(Point3D center, double r);
	Sphere(const Sphere& sphere);
	Sphere& operator=(const Sphere& sphere);
	virtual ~Sphere();

	virtual std::shared_ptr<Sphere> Clone() const;

	void SetCenter(const Point3D& c);
	void SetCenter(const double x, const double y, const double z);
	void SetRadius(const double r);
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;

private:
	Point3D mCenter;
	double mRadius;

	static const double kEpsilon;
};