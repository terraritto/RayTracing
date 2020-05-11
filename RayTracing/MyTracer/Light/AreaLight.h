#pragma once
#include "Light.h"
#include "../Material/Material.h"
#include "../Objects/GeometricObject.h"

class AreaLight :public Light
{
public:
	AreaLight();
	AreaLight(const AreaLight& light);
	~AreaLight();
	AreaLight& operator=(const AreaLight& rhs);
	std::shared_ptr<AreaLight> Clone() const;

	Vector3D GetDirection(ShadeRec& sr) override;
	bool InShadow(const Ray& ray, const ShadeRec& sr) const override;
	RGBColor L(ShadeRec& sr) override;
	float G(const ShadeRec& sr) const override;
	float pdf(const ShadeRec& sr) const override;

	void SetObject(std::shared_ptr<GeometricObject> object);
private:
	std::shared_ptr<GeometricObject> mObjectPtr;
	std::shared_ptr<Material> mMaterialPtr;
	Point3D mSamplePoint;
	Normal mLightNormal;
	Vector3D mWi;
};