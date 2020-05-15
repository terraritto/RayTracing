#pragma once
#include "BRDF.h"

enum class MicrofaseType
{
	GGX,
	Beckmann
};

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


	double FTerm(const Vector3D& wi, const Vector3D& wh) const //schlick
	{
		return mFrenel + (1 - mFrenel) * std::pow(1 - std::abs(wi * wh), 5);
	}

	double DTerm(const Vector3D& n, const Vector3D& h) const
	{
		double cosTheta = n * h;
		if (cosTheta < 1.0e-9)
		{
			return 0.0;
		}

		double cosTheta2 = cosTheta * cosTheta;
		double cosTheta4 = cosTheta2 * cosTheta2;
		double alpha2 = mAlpha * mAlpha;
		double chi = Heaviside(cosTheta);
		double tanTheta2 = (1.0 - cosTheta2) / cosTheta2;
		
		switch (mType)
		{
		case MicrofaseType::GGX:
			return chi / (PI * alpha2 * cosTheta4 * (std::pow(1.0 + tanTheta2 / alpha2, 2)));
		case MicrofaseType::Beckmann:
			return chi * std::exp(-tanTheta2 / alpha2) / (PI * alpha2 * cosTheta4);
		}
	}

	double Lambda(double cosTheta) const
	{
		double tanthetaO = std::sqrt(1.0 - cosTheta * cosTheta) / cosTheta;
		double a = 1.0 / (mAlpha * tanthetaO);
		switch (mType)
		{
		case MicrofaseType::GGX:
			return -1.0 + std::sqrt(1.0 + 1.0 / (a * a)) * 0.5;
		case MicrofaseType::Beckmann:
			return (std::erf(a) - 1) * 0.5 + std::exp(-a * a) / (2.0 * a * std::sqrt(PI));
		}
	}

	double GTerm(const Vector3D& wo, const Vector3D& wi, const Vector3D& wh, const Vector3D& n) const
	{
		double numer = Heaviside(wo * wh) * Heaviside(wi * wh);
		double denom = 1.0 + Lambda(wo * n) + Lambda(wi * n);

		return numer / denom;
	}

	void SetKs(const float k);
	void SetAlpha(const float alpha);
	void SetFresnel(const float fresnel);
	void SetType(MicrofaseType type);
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
	MicrofaseType mType;
};