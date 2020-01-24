#pragma once
#include "BTDF.h"

class FresnelTransmitter : public BTDF
{
public:
	FresnelTransmitter();
	FresnelTransmitter(const FresnelTransmitter& ft);
	std::shared_ptr<FresnelTransmitter> Clone() const;
	FresnelTransmitter& operator=(const FresnelTransmitter& rhs);
	~FresnelTransmitter();

	RGBColor Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;
	RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const override;
	RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const override;
	bool tir(const ShadeRec& sr) override;
	float Fresnel(const ShadeRec& sr) const;

	void SetEtaIn(const float eta);
	void SetEtaOut(const float eta);
protected:
	float mEtaIn;
	float mEtaOut;
};