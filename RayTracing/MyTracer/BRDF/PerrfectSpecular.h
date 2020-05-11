#pragma once
#include "BRDF.h"

class PerfectSpecular : public BRDF
{
public:
	PerfectSpecular();
	~PerfectSpecular();
	
	std::shared_ptr<PerfectSpecular> Clone() const;

	void SetKr(const float k);
	void SetCr(const RGBColor& c);
	void SetCr(const float r, const float g, const float b);
	void SetCr(const float c);
	RGBColor Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;
	RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const override;
	RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const override;
	RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const override;
private:
	float mKr; // reflection coefficient
	RGBColor mCr; // reflection color
};