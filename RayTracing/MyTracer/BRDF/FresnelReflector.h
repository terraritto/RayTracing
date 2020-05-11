#pragma once
#include "BRDF.h"

class FresnelReflector : public BRDF
{
public:
	FresnelReflector();
	~FresnelReflector();

	std::shared_ptr<FresnelReflector> Clone() const;

	void SetEtaIn(const float eta);
	void SetEtaOut(const float eta);
	RGBColor Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wr) const override;
	RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr) const override;
	RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr, float& pdf) const override;
	RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const override;
	float Fresnel(const ShadeRec& sr) const;
private:
	float mEtaIn;
	float mEtaOut;
};