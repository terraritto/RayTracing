#include "MicrofasetSpecular.h"
#include "../Sampler/MultiJittered.h"
#include "../Maths/Constants.h"

MicrofasetSpecular::MicrofasetSpecular()
	: BRDF(), mAlpha(0.0), mFrenel(0.0), mCs(0.0), mKs(0.0)
{
}

MicrofasetSpecular::MicrofasetSpecular(const MicrofasetSpecular& lamb)
	: BRDF(lamb), mAlpha(lamb.mAlpha), mFrenel(lamb.mFrenel), mCs(lamb.mCs), mKs(0.0)
{
}

MicrofasetSpecular& MicrofasetSpecular::operator=(const MicrofasetSpecular& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	BRDF::operator=(rhs);

	mAlpha = rhs.mAlpha;
	mFrenel = rhs.mFrenel;
	mCs = rhs.mCs;

	return *this;
}

MicrofasetSpecular::~MicrofasetSpecular()
{
}

std::shared_ptr<MicrofasetSpecular> MicrofasetSpecular::Clone() const
{
	return std::make_shared<MicrofasetSpecular>(*this);
}

RGBColor MicrofasetSpecular::Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	RGBColor L;
	auto wh = (wi + wo); //half vector
	wh.Normalize();
	
	double dotWi = wi * sr.mNormal;
	double dotWo = wo * sr.mNormal;

	return mKs * mCs * FTerm(wi, wh) * GTerm(wo, wi, wh, sr.mNormal) * DTerm(sr.mNormal, wh) / (4 * std::abs(dotWi) * std::abs(dotWo));
}

RGBColor MicrofasetSpecular::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const
{
	return RGBColor();
}

RGBColor MicrofasetSpecular::Rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return RGBColor();
}


double MicrofasetSpecular::FTerm(const Vector3D& wi, const Vector3D& wh) const //schlick
{
	return mFrenel + (1 - mFrenel) * std::pow(1 - std::abs(wi * wh),5);
}

double MicrofasetSpecular::DTerm(const Vector3D& n, const Vector3D& h) const
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

	return chi / (PI * alpha2 * cosTheta4 * (std::pow(1.0 + tanTheta2 / alpha2,2)));
}

double MicrofasetSpecular::Lambda(double cosTheta) const
{
	double tanthetaO = std::sqrt(1.0 - cosTheta * cosTheta) / cosTheta;
	double a = 1.0 / (mAlpha * tanthetaO);
	return -1.0 + std::sqrt(1.0 + 1.0 / (a * a)) * 0.5;
	/*
	double cosTheta2 = cosTheta * cosTheta;
	return (-1.0 + std::sqrt(1.0 + mAlpha * mAlpha * (1 - cosTheta2) / cosTheta2)) * 0.5;
	*/
}

double MicrofasetSpecular::GTerm(const Vector3D& wo, const Vector3D& wi, const Vector3D& wh, const Vector3D& n) const
{
	double numer = Heaviside(wo * wh) * Heaviside(wi * wh);
	double denom = 1.0 + Lambda(wo * n) + Lambda(wi * n);

	return numer / denom;
}

void MicrofasetSpecular::SetKs(const float k)
{
	mKs = k;
}

void MicrofasetSpecular::SetAlpha(const float alpha)
{
	mAlpha = alpha;
}

void MicrofasetSpecular::SetFresnel(const float fresnel)
{
	mFrenel = fresnel;
}

void MicrofasetSpecular::SetCs(const RGBColor& c)
{
	mCs = c;
}

void MicrofasetSpecular::SetCs(const float r, const float g, const float b)
{
	mCs = RGBColor(r, g, b);
}

void MicrofasetSpecular::SetCs(const float c)
{
	mCs = RGBColor(c);
}

void MicrofasetSpecular::SetSampler(std::shared_ptr<Sampler> sp)
{
	mSamplerPtr = sp;
	mSamplerPtr->MapSamplesToHemisphere(1);
}

void MicrofasetSpecular::SetSamples(const int numSamples)
{
	mSamplerPtr = std::make_shared<MultiJittered>(numSamples);
	mSamplerPtr->MapSamplesToHemisphere(1);
}
