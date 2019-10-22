#include "BRDF.h"
#include "..//Maths/Constants.h"

BRDF::BRDF()
	:mSamplerPtr(nullptr)
{

}

BRDF::BRDF(const BRDF& brdf)
{
	if (brdf.mSamplerPtr)
	{
		mSamplerPtr = brdf.mSamplerPtr->Clone();
	}
	else
	{
		mSamplerPtr = nullptr;
	}
}

BRDF& BRDF::operator=(const BRDF& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	if (mSamplerPtr)
	{
		mSamplerPtr.reset();
		mSamplerPtr = nullptr;
	}

	if (rhs.mSamplerPtr)
	{
		mSamplerPtr = rhs.mSamplerPtr->Clone();
	}

	return *this;
}

BRDF::~BRDF()
{
	if (mSamplerPtr)
	{
		mSamplerPtr.reset();
		mSamplerPtr = nullptr;
	}
}

void BRDF::SetSampler(std::shared_ptr<Sampler> sPtr)
{
	mSamplerPtr = sPtr;
	mSamplerPtr->MapSamplesToHemisphere(1); //for perfect diffuse
}

RGBColor BRDF::Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return black;
}

RGBColor BRDF::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const
{
	return black;
}

RGBColor BRDF::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const
{
	return black;
}

RGBColor BRDF::Rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return black;
}
