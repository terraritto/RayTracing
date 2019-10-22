#include "Directional.h"

Directional::Directional()
	: Light()
	, mLs(1.0)
	, mColor(1.0)
	, mDir(0, 1, 0)
{

}

Directional::Directional(const Directional& dl)
	: Light(dl)
	, mLs(dl.mLs)
	, mColor(dl.mColor)
	, mDir(dl.mDir)
{

}

Directional::~Directional()
{

}

Directional& Directional::operator=(const Directional& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Light::operator=(rhs);

	mLs = rhs.mLs;
	mColor = rhs.mColor;
	mDir = rhs.mDir;

	return *this;
}

std::shared_ptr<Directional> Directional::Clone() const
{
	return std::make_shared<Directional>(*this);
}

void Directional::SetScaleRadiance(const float b)
{
	mLs = b;
}

void Directional::SetColor(const float c)
{
	mColor.mRed = c;
	mColor.mGreen = c;
	mColor.mBlue = c;
}

void Directional::SetColor(const RGBColor& c)
{
	mColor = c;
}

void Directional::SetColor(const float r, const float g, const float b)
{
	mColor.mRed = r;
	mColor.mGreen = g;
	mColor.mBlue = b;
}

void Directional::SetDirection(Vector3D d)
{
	mDir = d;
	mDir.Normalize();
}

void Directional::SetDirection(float dx, float dy, float dz)
{
	mDir.mPosX = dx;
	mDir.mPosY = dy;
	mDir.mPosZ = dz;
	mDir.Normalize();
}

Vector3D Directional::GetDirection(ShadeRec& sr)
{
	return mDir;
}

RGBColor Directional::L(ShadeRec& sr)
{
	return mLs * mColor;
}
