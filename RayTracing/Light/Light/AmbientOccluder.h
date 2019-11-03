#pragma once
#include "Light.h"
#include "../Sampler/Sampler.h"

class AmbientOccluder : public Light
{
public:
	AmbientOccluder();
	AmbientOccluder(const AmbientOccluder& ambient);
	AmbientOccluder& operator=(const AmbientOccluder& rhs);
	std::shared_ptr<AmbientOccluder> Clone() const;

	Vector3D GetDirection(ShadeRec& sr) override;
	bool InShadow(const Ray& ray, const ShadeRec& sr)const override;
	RGBColor L(ShadeRec& sr) override;

	void SetSampler(std::shared_ptr<Sampler> sPtr);
	void SetRadiance(float l);
	void SetColor(RGBColor min);
	void SetColor(float a);
	void SetColor(float r, float g, float b);
	void SetMinAmount(float ma);
private:
	Vector3D mU, mV, mW;
	std::shared_ptr<Sampler> mSamplerPtr;
	float mLs;
	RGBColor mColor;
	float mMinAmount;
};