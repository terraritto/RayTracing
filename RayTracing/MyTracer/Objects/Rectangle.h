#pragma once
#include "GeometricObject.h"
#include "../Maths/Point3D.h"
#include "../Maths/Vector3D.h"
#include "../Maths/Normal.h"
#include "../Sampler/Sampler.h"
#include "../Maths/Ray.h"
#include "../Utility/ShadeRec.h"

class Rectangler : public GeometricObject
{
public:
	Rectangler();
	Rectangler(Point3D p0, Vector3D a, Vector3D b, Normal n);
	Rectangler(Point3D p0, Vector3D a, Vector3D b);
	Rectangler(const Rectangler& rect);
	Rectangler& operator=(const Rectangler& rhs);
	std::shared_ptr<Rectangler> Clone() const;
	~Rectangler();

	virtual bool hit(const Ray& ray, double& tMin, ShadeRec& s);
	bool Shadow_hit(const Ray& ray, float& tMin) const override;

	void SetP0(const Point3D p0);
	Point3D GetP0() const;
	void SetAB(Vector3D a, Vector3D b);
	void SetSampler(std::shared_ptr<Sampler> sampler);
	Point3D Sample() override;
	float pdf(const ShadeRec& sr) override;
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