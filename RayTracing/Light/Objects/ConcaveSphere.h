#pragma once
#pragma once
#include "GeometricObject.h"
#include "../Maths/Point3D.h"
#include "../Utility/ShadeRec.h"
#include "../Maths/Ray.h"

class ShadeRec;

class ConcaveSphere : public GeometricObject
{
public:
	ConcaveSphere();
	ConcaveSphere(Point3D center, double r);
	ConcaveSphere(const ConcaveSphere& ConcaveSphere);
	ConcaveSphere& operator=(const ConcaveSphere& ConcaveSphere);
	virtual ~ConcaveSphere();

	virtual std::shared_ptr<ConcaveSphere> Clone() const;

	void SetCenter(const Point3D& c);
	void SetCenter(const double x, const double y, const double z);
	void SetRadius(const double r);
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s);
	bool Shadow_hit(const Ray& ray, float& tmin) const override;
private:
	Point3D mCenter;
	double mRadius;

	static const double kEpsilon;
};