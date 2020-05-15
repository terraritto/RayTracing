#include "MicrofasetSpecular.h"
#include "../Sampler/MultiJittered.h"

MicrofasetSpecular::MicrofasetSpecular()
	: BRDF(), mAlpha(0.0), mFrenel(0.0), mCs(0.0), mKs(0.0), mType(MicrofaseType::GGX)
{
}

MicrofasetSpecular::MicrofasetSpecular(const MicrofasetSpecular& lamb)
	: BRDF(lamb), mAlpha(lamb.mAlpha), mFrenel(lamb.mFrenel), mCs(lamb.mCs), mKs(0.0), mType(lamb.mType)
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
	mType = rhs.mType;

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

void MicrofasetSpecular::SetType(MicrofaseType type)
{
	mType = type;
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
