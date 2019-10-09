#pragma once
#include "BRDF.h"

class Lambertian : public BRDF
{
public:
	Lambertian();
	Lambertian(const Lambertian& lamb);
	Lambertian& operator=(const Lambertian& rhs);
	~Lambertian();

	std::shared_ptr<BRDF> Clone() const override;
	RGBColor Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;
	virtual RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const override;
	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const override;
	
	void SetKa(const float ka);
	void SetKd(const float kd);
	void SetCd(const RGBColor& c);
	void SetCd(const float r, const float g, const float b);
	void SetCd(const float c);
private:
	float mKd;
	RGBColor mCd;
};