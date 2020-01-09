#include "PerrfectSpecular.h"

PerfectSpecular::PerfectSpecular()
	: BRDF()
	, mKr(0.0)
	, mCr(1.0)
{
}

PerfectSpecular::~PerfectSpecular()
{
}

std::shared_ptr<PerfectSpecular> PerfectSpecular::Clone() const
{
	return std::make_shared<PerfectSpecular>(*this);
}

void PerfectSpecular::SetKr(const float k)
{
	mKr = k;
}

void PerfectSpecular::SetCr(const RGBColor& c)
{
	mCr = c;
}

void PerfectSpecular::SetCr(const float r, const float g, const float b)
{
	mCr = RGBColor(r, g, b);
}

void PerfectSpecular::SetCr(const float c)
{
	mCr = RGBColor(c);
}

RGBColor PerfectSpecular::Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return black;
}

RGBColor PerfectSpecular::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const
{
	float nDotWo = sr.mNormal * wo;
	wi = -wo + 2.0 * sr.mNormal * nDotWo;
	return (mKr * mCr / std::fabs(sr.mNormal * wi));
}

RGBColor PerfectSpecular::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const
{
	return black;
}

RGBColor PerfectSpecular::Rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return black;
}
