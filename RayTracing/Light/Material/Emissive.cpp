#include "Emissive.h"

Emissive::Emissive()
	: Material()
	, mLs(0.5)
	, mCe()
{
}

Emissive::Emissive(const Emissive& e)
	: Material(e)
	, mLs(e.mLs)
	, mCe(e.mCe)
{
}

Emissive::~Emissive()
{
}

Emissive& Emissive::operator=(const Emissive& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Material::operator=(rhs);
	mLs = rhs.mLs;
	mCe = rhs.mCe;

	return *this;
}

std::shared_ptr<Emissive> Emissive::Clone() const
{
	return std::make_shared<Emissive>(*this);
}

void Emissive::SetLadiance(const float ls)
{
	mLs = ls;
}

void Emissive::SetCe(const RGBColor c)
{
	mCe = c;
}

void Emissive::SetCe(const float r, const float g, const float b)
{
	mCe = RGBColor(r, g, b);
}

void Emissive::SetCe(const float c)
{
	mCe = RGBColor(c);
}

RGBColor Emissive::Shade(ShadeRec& sr)
{
	if (-sr.mNormal * sr.mRay.mDirection > 0.0)
	{
		return mLs * mCe;
	}
	else
	{
		return black;
	}
}

RGBColor Emissive::AreaLightShade(ShadeRec& sr)
{
	if (-sr.mNormal * sr.mRay.mDirection > 0.0)
	{
		return mLs * mCe;
	}
	else
	{
		return black;
	}
}

RGBColor Emissive::GetLe(ShadeRec& sr) const
{
	return mLs * mCe;
}
