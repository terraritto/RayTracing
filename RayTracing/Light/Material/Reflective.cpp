#include "Reflective.h"

Reflective::Reflective()
	: Phong()
	, mReflectiveBRDF(std::make_shared<PerfectSpecular>())
{
}

Reflective::Reflective(const Reflective& re)
	: Phong(re)
{
	if (re.mReflectiveBRDF)
	{
		mReflectiveBRDF = re.mReflectiveBRDF->Clone();
	}
	else
	{
		mReflectiveBRDF = std::make_shared<PerfectSpecular>();
	}
}

Reflective::~Reflective()
{
}

Reflective& Reflective::operator=(const Reflective& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Phong::operator=(rhs);

	mReflectiveBRDF = nullptr;
	
	if (rhs.mReflectiveBRDF)
	{
		mReflectiveBRDF = rhs.mReflectiveBRDF->Clone();
	}

	return *this;
}

std::shared_ptr<Reflective> Reflective::Clone() const
{
	return std::make_shared<Reflective>(*this);
}

void Reflective::SetKr(const float k)
{
	mReflectiveBRDF->SetKr(k);
}

void Reflective::SetCr(const RGBColor& c)
{
	mReflectiveBRDF->SetCr(c);
}

void Reflective::SetCr(const float r, const float g, const float b)
{
	mReflectiveBRDF->SetCr(r, g, b);
}

void Reflective::SetCr(const float c)
{
	mReflectiveBRDF->SetCr(c);
}

RGBColor Reflective::Shade(ShadeRec& sr)
{
	RGBColor L(Phong::Shade(sr));

	Vector3D wo = -sr.mRay.mDirection;
	Vector3D wi;
	RGBColor fr = mReflectiveBRDF->SampleFunc(sr, wo, wi);
	
	Ray reflectedRay(sr.mHitPoint, wi);

	L += fr * sr.mWorld.mTracerPtr->TraceRay(reflectedRay, sr.mDepth + 1) *
		(sr.mNormal * wi);

	return L;
}

RGBColor Reflective::PathShade(ShadeRec& sr)
{
	Vector3D wo = -sr.mRay.mDirection;
	Vector3D wi;
	float pdf;
	RGBColor fr = mReflectiveBRDF->SampleFunc(sr, wo, wi, pdf);
	Ray reflected_ray(sr.mHitPoint, wi);

	return fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, sr.mDepth + 1) * (sr.mNormal * wi) / pdf;
}

RGBColor Reflective::GlobalShade(ShadeRec& sr)
{
	Vector3D wo = -sr.mRay.mDirection;
	Vector3D wi;
	float pdf;
	RGBColor fr = mReflectiveBRDF->SampleFunc(sr, wo, wi, pdf);
	Ray reflected_ray(sr.mHitPoint, wi);

	if (sr.mDepth == 0)
	{
		return fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, sr.mDepth + 2) * (sr.mNormal * wi) / pdf;
	}
	else
	{
		return fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, sr.mDepth + 1) * (sr.mNormal * wi) / pdf;
	}
}

RGBColor Reflective::AreaLightShade(ShadeRec& sr)
{
	RGBColor L(Phong::Shade(sr));

	Vector3D wo = -sr.mRay.mDirection;
	Vector3D wi;
	RGBColor fr = mReflectiveBRDF->SampleFunc(sr, wo, wi);

	Ray reflectedRay(sr.mHitPoint, wi);

	L += fr * sr.mWorld.mTracerPtr->TraceRay(reflectedRay, sr.mDepth + 1) *
		(sr.mNormal * wi);

	return L;

}
