#include "WrappedFBmTexture.h"

WrappedTexture::WrappedTexture()
	: mNoisePtr(nullptr)
	, mColor(black)
	, mExpansionNumber(10)
{
}

WrappedTexture::~WrappedTexture()
{
}

RGBColor WrappedTexture::GetColor(const ShadeRec& sr) const
{
	float noise = mExpansionNumber * mNoisePtr->ValuefBm(sr.mLocalHitPoint);
	float value = noise - std::floor(noise);

	return value * mColor;
}

void WrappedTexture::SetNoise(std::shared_ptr<LatticeNoise> noise)
{
	mNoisePtr = noise;
}

void WrappedTexture::SetColor(const RGBColor& col)
{
	mColor = col;
}

void WrappedTexture::SetExpansionNumber(const float num)
{
	mExpansionNumber = num;
}
