#include "Ambient.h"

Ambient::Ambient()
	: Light()
	, mLs(1.0)
	, mColor(1.0)
{

}

Ambient::Ambient(const Ambient& a)
	: Light(a)
	, mLs(a.mLs)
	, mColor(a.mColor)
{
}

Ambient::~Ambient()
{

}

Ambient& Ambient::operator=(const Ambient& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Light::operator=(rhs);

	mLs = rhs.mLs;
	mColor = rhs.mColor;

	return *this;
}

std::shared_ptr<Ambient> Ambient::Clone() const
{
	return std::make_shared<Ambient>(*this);
}

Vector3D Ambient::GetDirection(ShadeRec& s)
{
	return Vector3D(0.0);
}

RGBColor Ambient::L(ShadeRec& s)
{
	return mLs * mColor;
}

void Ambient::SetScaleRadiance(const float b)
{
	mLs = b;
}

void Ambient::SetColor(const float c)
{
	mColor.mRed = c;
	mColor.mGreen = c;
	mColor.mBlue = c;
}

void Ambient::SetColor(const RGBColor& c)
{
	mColor = c;
}

void Ambient::SetColor(const float r, const float g, const float b)
{
	mColor.mRed = r;
	mColor.mGreen = g;
	mColor.mBlue = b;
}
