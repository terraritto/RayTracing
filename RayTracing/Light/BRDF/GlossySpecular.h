#pragma once
#include "BRDF.h"

class GlossySpecular :public BRDF
{
public:
	GlossySpecular();
	~GlossySpecular();

	std::shared_ptr<GlossySpecular> Clone() const;
	RGBColor Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;
	//RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const override;
	RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const;

	void SetKs(const float k);
	void SetExp(const float exp);
	void SetCs(const RGBColor& c);
	void SetCs(const float r, const float g, const float b);
	void SetCs(const float c);
private:
	float mKs;
	RGBColor mCs;
	float mExp;
};