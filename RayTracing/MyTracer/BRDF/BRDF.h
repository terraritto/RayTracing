#pragma once

#include "..//Utility/RGBColor.h"
#include "..//Maths/Vector3D.h"
#include "..//Utility/ShadeRec.h"
#include "..//Sampler/Sampler.h"

class BRDF
{
public:
	BRDF();
	BRDF(const BRDF& brdf);
	std::shared_ptr<BRDF> Clone() const;
	BRDF& operator=(const BRDF& rhs);
	virtual ~BRDF();

	void SetSampler(std::shared_ptr<Sampler> sPtr);

	virtual RGBColor Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
	virtual RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
	virtual RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const;

	//for alpha
	virtual float GetAlpha(const ShadeRec& sr) { return 1.0f; }
protected:
	std::shared_ptr<Sampler> mSamplerPtr;
};