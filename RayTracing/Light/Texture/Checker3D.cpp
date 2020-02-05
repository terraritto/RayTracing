#include "Checker3D.h"

Checker3D::Checker3D()
	: mColor1(black)
	, mColor2(white)
	, mSize(1.0)
{
}

Checker3D::~Checker3D()
{
}

void Checker3D::SetColor1(const RGBColor& color)
{
	mColor1 = color;
}

void Checker3D::SetColor2(const RGBColor& color)
{
	mColor2 = color;
}

void Checker3D::SetSize(const float s)
{
	mSize = s;
}

RGBColor Checker3D::GetColor(const ShadeRec& sr) const
{
	float eps = -0.000187453738;
	float x = sr.mLocalHitPoint.mPosX + eps;
	float y = sr.mLocalHitPoint.mPosY + eps;
	float z = sr.mLocalHitPoint.mPosZ + eps;

	if (
		(static_cast<int>(std::floor(x / mSize)) +
		static_cast<int>(std::floor(y / mSize)) +
		static_cast<int>(std::floor(z / mSize))) % 2 == 0
		)
	{
		return mColor1;
	}
	else
	{
		return mColor2;
	}
}
