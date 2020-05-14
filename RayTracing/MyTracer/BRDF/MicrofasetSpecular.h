#pragma once
#include "BRDF.h"

class MicrofasetSpecular : public BRDF
{
public:
	MicrofasetSpecular();
	MicrofasetSpecular(const MicrofasetSpecular& lamb);
	MicrofasetSpecular& operator=(const MicrofasetSpecular& rhs);
	~MicrofasetSpecular();

	std::shared_ptr<MicrofasetSpecular> Clone() const;
	RGBColor Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;
	RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const override;
	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const override;

	double FTerm(const Vector3D& wo, const Vector3D& wh) const;
	double DTerm(const Vector3D& n, const Vector3D& h) const;
	double Lambda(double cosTheta) const;
	double GTerm(const Vector3D& wi, const Vector3D& wo, const Vector3D& wh, const Vector3D& n) const;
	inline double ChiPlus(double x) { return x < 0.0 ? 0.0 : 1.0; }

	void SetKs(const float k);
	void SetAlpha(const float alpha);
	void SetFresnel(const float fresnel);
	void SetCs(const RGBColor& c);
	void SetCs(const float r, const float g, const float b);
	void SetCs(const float c);

	void SetSampler(std::shared_ptr<Sampler> sp);
	void SetSamples(const int numSamples);
private:
	double mAlpha;
	double mFrenel;
	RGBColor mCs;
	double mKs;
};