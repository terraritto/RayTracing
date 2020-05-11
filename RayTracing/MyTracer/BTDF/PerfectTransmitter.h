#pragma once
#include "BTDF.h"

class PerfectTransmitter : public BTDF
{
public:
	PerfectTransmitter();
	PerfectTransmitter(const PerfectTransmitter& pt);
	std::shared_ptr<PerfectTransmitter> Clone() const;
	PerfectTransmitter& operator=(const PerfectTransmitter& rhs);
	~PerfectTransmitter();

	RGBColor Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;
	RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const override;
	RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const override;
	bool tir(const ShadeRec& sr) override;

	void SetKt(const float kt);
	void SetIor(const float ior);
protected:
	float mKt;
	float mIor;

};