#include "PlaneChecker.h"

PlaneChecker::PlaneChecker()
	: mColor1(black)
	, mColor2(white)
	, mOutlineColor(black)
	, mOutlineWidth(0.0)
	, mSize(1.0)
{
}

PlaneChecker::~PlaneChecker()
{
}

void PlaneChecker::SetColor1(const RGBColor& color)
{
	mColor1 = color;
}

void PlaneChecker::SetColor2(const RGBColor& color)
{
	mColor2 = color;
}

void PlaneChecker::SetOutlineColor(const RGBColor& color)
{
	mOutlineColor = color;
}

void PlaneChecker::SetSize(const float s)
{
	mSize = s;
}

void PlaneChecker::SetOutlineWidth(const float ow)
{
	mOutlineWidth = ow;
}

RGBColor PlaneChecker::GetColor(const ShadeRec& sr) const
{
	float x = sr.mLocalHitPoint.mPosX;
	float z = sr.mLocalHitPoint.mPosZ;
	int ix = std::floor(x / mSize);
	int iz = std::floor(z / mSize);
	float fx = x / mSize - ix;
	float fz = z / mSize - iz;
	float width = 0.5 * mOutlineWidth / mSize;
	bool isInOutline = (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);

	if (isInOutline)
	{
		return mOutlineColor;
	}

	if ((ix + iz) % 2 == 0)
	{
		return mColor1;
	}
	else
	{
		return mColor2;
	}
}
