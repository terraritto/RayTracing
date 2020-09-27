#include "SV_Lambertian.h"
#include "..//Maths/Constants.h"
#include "../Sampler/MultiJittered.h"

SV_Lambertian::SV_Lambertian()
	: BRDF()
	, mKd(0.0)
	, mCd(nullptr)
{

}

SV_Lambertian::SV_Lambertian(const SV_Lambertian& lamb)
	: BRDF(lamb)
	, mKd(lamb.mKd)
	, mCd(lamb.mCd)
{
	mSamplerPtr->MapSamplesToHemisphere(1);
}

SV_Lambertian& SV_Lambertian::operator=(const SV_Lambertian& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	BRDF::operator=(rhs);

	mKd = rhs.mKd;
	if (rhs.mCd)
	{
		mCd = rhs.mCd;
	}
	else
	{
		mCd = std::make_shared<Texture>();
	}

	return *this;
}

SV_Lambertian::~SV_Lambertian()
{

}

std::shared_ptr<SV_Lambertian> SV_Lambertian::Clone() const
{
	return std::make_shared<SV_Lambertian>(*this);
}

RGBColor SV_Lambertian::Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return mKd * mCd->GetColor(sr) * INVPI;
}

RGBColor SV_Lambertian::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const
{
	Vector3D w = sr.mNormal;
	Vector3D v = Vector3D(0.0034, 1.0, 0.0071) ^ w;
	v.Normalize();
	Vector3D u = v ^ w;

	Point3D sp = mSamplerPtr->SampleHemisphere();
	wi = sp.mPosX * u + sp.mPosY * v + sp.mPosZ * w;
	wi.Normalize();
	pdf = sr.mNormal * wi * INVPI;

	return mKd * mCd->GetColor(sr) * INVPI;
}

RGBColor SV_Lambertian::Rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return mKd * mCd->GetColor(sr);
}

float SV_Lambertian::GetAlpha(const ShadeRec& sr)
{
	return mCd->GetAlpha(sr);
}

//Material may have no toon texture,
//so process add when mToon is nullptr.
RGBColor SV_Lambertian::GetToonColor(float sample)
{
	if (mToon) {
		return mToon->GetToon(sample);
	}
	else
	{
		return RGBColor(sample);
	}
}

void SV_Lambertian::SetKa(const float ka)
{
	mKd = ka;
}

void SV_Lambertian::SetKd(const float kd)
{
	mKd = kd;
}

void SV_Lambertian::SetCd(std::shared_ptr<Texture> cd)
{
	mCd = cd;
}

void SV_Lambertian::SetToon(std::shared_ptr<Texture> toon)
{
	mToon = toon;
}

void SV_Lambertian::SetSampler(std::shared_ptr<Sampler> sp)
{
	mSamplerPtr = sp;
	mSamplerPtr->MapSamplesToHemisphere(1);
}

void SV_Lambertian::SetSamples(const int numSamples)
{
	mSamplerPtr = std::make_shared<MultiJittered>(numSamples);
	mSamplerPtr->MapSamplesToHemisphere(1);
}
