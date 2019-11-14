#pragma once
#include "GeometricObject.h"
#include "../Maths/Point3D.h"
#include "../Maths/Vector3D.h"
#include "../Maths/Normal.h"
#include "../Sampler/Sampler.h"
#include "../Maths/Ray.h"
#include "../Utility/ShadeRec.h"

class Rectangle : public GeometricObject
{
public:
	Rectangle(Point3D p0, Vector3D a, Vector3D b, Normal n);
	Rectangle(const Rectangle& rect);
	Rectangle& operator=(const Rectangle& rhs);
	std::shared_ptr<Rectangle> Clone() const;
	~Rectangle();

	virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;
	bool Shadow_hit(const Ray& ray, float& tmin) const override;

	void SetP0(const Point3D p0);
	Point3D GetP0() const;
	void SetAB(const Vector3D a, const Vector3D b);
	void SetSampler(std::shared_ptr<Sampler> sampler);
	Point3D Sample() override;
	Normal GetNormal(const Point3D& p) override;
private:
	Point3D mP0;
	Vector3D mA;
	Vector3D mB;
	Normal mNormal;
	std::shared_ptr<Sampler> mSamplePtr;
	float mArea;
	float mInvArea;
	float mALenSquared;
	float mBLenSquared;
};