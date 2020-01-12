#include "GlossySpecular.h"
#include "../Sampler/MultiJittered.h"
#include <cmath>
#include "DxLib.h"

GlossySpecular::GlossySpecular()
	: BRDF()
	, mKs(0.0)
	, mCs(0.0)
	, mExp(1.0)
{
}

GlossySpecular::~GlossySpecular()
{

}

std::shared_ptr<GlossySpecular> GlossySpecular::Clone() const
{
	return std::make_shared<GlossySpecular>(*this);
}

// reciprofical glossy specular BRDF (Lewis,1994)

RGBColor GlossySpecular::Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	RGBColor L;
	float nDotWi = sr.mNormal * wi;
	Vector3D r(-wi + 2.0 * sr.mNormal * nDotWi);
	r.Normalize(); //r is unit vector
	float rDotWo = r * wo;
	
	if (rDotWo > 0.0)
	{
		L = mKs * mCs * std::pow(rDotWo, mExp);
	}

	return L;
}

RGBColor GlossySpecular::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const
{
	float nDotWo = sr.mNormal * wo;
	Vector3D r = -wo + 2.0 * sr.mNormal * nDotWo;

	Vector3D w = r;
	Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
	u.Normalize();
	Vector3D v = u ^ w;

	Point3D sp = mSamplerPtr->SampleHemisphere();
	wi = sp.mPosX * u + sp.mPosY * v + sp.mPosZ * w;

	if (sr.mNormal * wi < 0.0)
	{
		wi = -sp.mPosX * u - sp.mPosY * v + sp.mPosZ * w;
	}

	float phong_lobe = std::pow(r * wi, mExp);
	pdf = phong_lobe * (sr.mNormal * wi);

	return mKs * mCs * phong_lobe;
}


// Phong's specular model (Blinn, 1977)
/*
RGBColor GlossySpecular::Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	RGBColor L;
	auto h = (wi + wo);
	h.Normalize();
	float rDotWo = h * sr.mNormal; // operator has vector3d * normal

	if (rDotWo > 0.0)
	{
		L = mKs * mCs * std::pow(rDotWo, mExp);
	}

	return L;
}
*/

RGBColor GlossySpecular::Rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return black;
}

void GlossySpecular::SetKs(const float k)
{
	mKs = k;
}

void GlossySpecular::SetExp(const float exp)
{
	mExp = exp;
}

void GlossySpecular::SetCs(const RGBColor& c)
{
	mCs = c;
}

void GlossySpecular::SetCs(const float r, const float g, const float b)
{
	mCs.mRed = r;
	mCs.mGreen = g;
	mCs.mBlue = b;
}

void GlossySpecular::SetCs(const float c)
{
	mCs.mRed = c;
	mCs.mGreen = c;
	mCs.mBlue = c;
}

void GlossySpecular::SetSampler(std::shared_ptr<Sampler> sp, const float exp)
{
	mSamplerPtr = sp;
	mSamplerPtr->MapSamplesToHemisphere(exp);
}

void GlossySpecular::SetSamples(const int numSamples, const float exp)
{
	mSamplerPtr = std::make_shared<MultiJittered>(numSamples);
	mSamplerPtr->MapSamplesToHemisphere(exp);
}
