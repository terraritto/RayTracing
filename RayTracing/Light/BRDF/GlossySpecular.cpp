#include "GlossySpecular.h"
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
/*
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
*/

// Phong's specular model (Blinn, 1977)
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
