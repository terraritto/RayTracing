#pragma once
#include "GeometricObject.h"
#include "../Maths/Point3D.h"
#include "../Utility/ShadeRec.h"
#include "../Maths/Ray.h"
#include "../Maths/Normal.h"

class Box : public GeometricObject
{
public:
	Box(const Point3D& p0, const Point3D& p1);
	Box(const Box& box);
	~Box();
	Box& operator=(Box& rhs);

	std::shared_ptr<Box> Clone() const;
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s);
	bool Shadow_hit(const Ray& ray, float& t) const override;
	Normal GetNormal(const int faceHit) const;

	void SetP0(const Point3D p0);
	Point3D GetP0() const;
	void SetP1(const Point3D p1);
	Point3D GetP1() const;

private:
	Point3D mP0;
	Point3D mP1;
};