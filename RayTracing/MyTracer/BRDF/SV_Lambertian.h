#pragma once
#include "BRDF.h"
#include "../Texture/Texture.h"
#include <memory>

class SV_Lambertian : public BRDF
{
public:
	SV_Lambertian();
	SV_Lambertian(const SV_Lambertian& lamb);
	SV_Lambertian& operator=(const SV_Lambertian& rhs);
	~SV_Lambertian();

	std::shared_ptr<SV_Lambertian> Clone() const;
	RGBColor Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;
	RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const override;
	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const override;
	float GetAlpha(const ShadeRec& sr) override;
	
	RGBColor GetToonColor(float sample);

	void SetKa(const float ka);
	void SetKd(const float kd);
	void SetCd(std::shared_ptr<Texture> cd);
	void SetToon(std::shared_ptr<Texture> toon);

	void SetSampler(std::shared_ptr<Sampler> sp);
	void SetSamples(const int numSamples);
private:
	float mKd;
	std::shared_ptr<Texture> mCd;
	std::shared_ptr<Texture> mToon;
};