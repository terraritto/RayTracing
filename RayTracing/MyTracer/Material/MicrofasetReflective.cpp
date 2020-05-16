#include "MicrofasetReflective.h"

MicforasetReflective::MicforasetReflective()
	: CookTorrance()
	, mReflectiveBRDF(std::make_shared<PerfectSpecular>())
{
}

MicforasetReflective::MicforasetReflective(const MicforasetReflective& re)
	: CookTorrance(re)
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

MicforasetReflective::~MicforasetReflective()
{
}

MicforasetReflective& MicforasetReflective::operator=(const MicforasetReflective& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	CookTorrance::operator=(rhs);

	mReflectiveBRDF = nullptr;

	if (rhs.mReflectiveBRDF)
	{
		mReflectiveBRDF = rhs.mReflectiveBRDF->Clone();
	}

	return *this;
}

std::shared_ptr<MicforasetReflective> MicforasetReflective::Clone() const
{
	return std::make_shared<MicforasetReflective>(*this);
}

void MicforasetReflective::SetKr(const float k)
{
	mReflectiveBRDF->SetKr(k);
}

void MicforasetReflective::SetCr(const RGBColor& c)
{
	mReflectiveBRDF->SetCr(c);
}

void MicforasetReflective::SetCr(const float r, const float g, const float b)
{
	mReflectiveBRDF->SetCr(r,g,b);
}

void MicforasetReflective::SetCr(const float c)
{
	mReflectiveBRDF->SetCr(c);
}

RGBColor MicforasetReflective::Shade(ShadeRec& sr)
{
	RGBColor L(CookTorrance::Shade(sr));

	Vector3D wo = -sr.mRay.mDirection;
	Vector3D wi;
	RGBColor fr = mReflectiveBRDF->SampleFunc(sr, wo, wi);

	Ray reflectedRay(sr.mHitPoint, wi);

	L += fr * sr.mWorld.mTracerPtr->TraceRay(reflectedRay, sr.mDepth + 1) *
		(sr.mNormal * wi);

	return L;

}

RGBColor MicforasetReflective::PathShade(ShadeRec& sr)
{
	Vector3D wo = -sr.mRay.mDirection;
	Vector3D wi;
	float pdf;
	RGBColor fr = mReflectiveBRDF->SampleFunc(sr, wo, wi, pdf);
	Ray reflected_ray(sr.mHitPoint, wi);

	return fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, sr.mDepth + 1) * (sr.mNormal * wi) / pdf;

}

RGBColor MicforasetReflective::GlobalShade(ShadeRec& sr)
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

RGBColor MicforasetReflective::AreaLightShade(ShadeRec& sr)
{
	RGBColor L(CookTorrance::Shade(sr));

	Vector3D wo = -sr.mRay.mDirection;
	Vector3D wi;
	RGBColor fr = mReflectiveBRDF->SampleFunc(sr, wo, wi);

	Ray reflectedRay(sr.mHitPoint, wi);

	L += fr * sr.mWorld.mTracerPtr->TraceRay(reflectedRay, sr.mDepth + 1) *
		(sr.mNormal * wi);

	return L;

}
