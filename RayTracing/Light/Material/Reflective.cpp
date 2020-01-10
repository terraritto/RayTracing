#include "Reflective.h"

Reflective::Reflective()
	: Phong()
	, mReflectiveBRDF(std::make_shared<PerfectSpecular>())
{
}

Reflective::Reflective(const Reflective& re)
	: Phong()
{
	if (re.mReflectiveBRDF)
	{
		mReflectiveBRDF = re.mReflectiveBRDF->Clone();
	}
	else
	{
		mReflectiveBRDF = nullptr;
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
	return std::make_shared<Reflective>();
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
