#include "GlossyReflector.h"

GlossyReflector::GlossyReflector()
	: Phong()
	, mGlossySpecularBRDF(std::make_shared<GlossySpecular>())
{
}

GlossyReflector::GlossyReflector(const GlossyReflector& re)
	: Phong(re)
{
	if (re.mGlossySpecularBRDF)
	{
		mGlossySpecularBRDF = re.mGlossySpecularBRDF->Clone();
	}
	else
	{
		mGlossySpecularBRDF = std::make_shared<GlossySpecular>();
	}
}

GlossyReflector::~GlossyReflector()
{
}

GlossyReflector& GlossyReflector::operator=(const GlossyReflector& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Phong::operator=(rhs);

	mGlossySpecularBRDF = nullptr;

	if (rhs.mGlossySpecularBRDF)
	{
		mGlossySpecularBRDF = rhs.mGlossySpecularBRDF;
	}

	return *this;
}

std::shared_ptr<GlossyReflector> GlossyReflector::Clone() const
{
	return std::make_shared<GlossyReflector>(*this);
}

void GlossyReflector::SetSampler(std::shared_ptr<Sampler> sp, const float exp)
{
	mGlossySpecularBRDF->SetSampler(sp, exp);
}

void GlossyReflector::SetSamples(const int numSamples, const float exp)
{
	mGlossySpecularBRDF->SetSamples(numSamples, exp);
}

void GlossyReflector::SetKr(const float k)
{
	mGlossySpecularBRDF->SetKs(k);
}

void GlossyReflector::SetCr(const RGBColor r)
{
	mGlossySpecularBRDF->SetCs(r);
}

void GlossyReflector::SetCr(const float r, const float g, const float b)
{
	mGlossySpecularBRDF->SetCs(r, g, b);
}

void GlossyReflector::SetCr(const float c)
{
	mGlossySpecularBRDF->SetCs(c);
}

void GlossyReflector::SetExponent(const float exp)
{
	mGlossySpecularBRDF->SetExp(exp);
}

RGBColor GlossyReflector::AreaLightShade(ShadeRec& sr)
{
	RGBColor L(Phong::AreaLightShade(sr));
	Vector3D wo(-sr.mRay.mDirection);
	Vector3D wi;
	float pdf;
	RGBColor fr(mGlossySpecularBRDF->SampleFunc(sr, wo, wi, pdf));
	Ray reflectedRay(sr.mHitPoint, wi);

	L += fr * sr.mWorld.mTracerPtr->TraceRay(reflectedRay, sr.mDepth + 1) *
		(sr.mNormal * wi) / pdf;

	return L;
}
