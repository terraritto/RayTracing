#pragma once
#include "Light.h"

class EnvironmentLight : public Light
{
public:
	EnvironmentLight();
	EnvironmentLight(const EnvironmentLight& light);
	~EnvironmentLight();
	EnvironmentLight& operator=(const EnvironmentLight& rhs);

	std::shared_ptr<EnvironmentLight> Clone();

	void SetSampler(std::shared_ptr<Sampler> sampler);
	void SetMaterial(std::shared_ptr<Material> material);
	Vector3D GetDirection(ShadeRec& sr) override;
	RGBColor L(ShadeRec& sr) override;
	bool InShadow(const Ray& ray, const ShadeRec& sr) const override;
	float pdf(const ShadeRec& sr) const override;
private:
	std::shared_ptr<Sampler> mSamplerPtr;
	std::shared_ptr<Material> mMaterialPtr;
	Vector3D mU, mV, mW;
	Vector3D mWi;
};