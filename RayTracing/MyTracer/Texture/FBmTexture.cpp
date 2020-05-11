#include "FBmTexture.h"

FBmTexture::FBmTexture()
	: mNoisePtr(nullptr)
	, mColor(black)
	, mMinValue(0.0f)
	, mMaxValue(1.0f)
{
}

FBmTexture::~FBmTexture()
{
}

RGBColor FBmTexture::GetColor(const ShadeRec& sr) const
{
	float value = mNoisePtr->ValuefBm(sr.mLocalHitPoint);	
	value = std::abs(mMinValue + (mMaxValue - mMinValue) * value);

	return value * mColor;
}

void FBmTexture::SetNoise(std::shared_ptr<LatticeNoise> noise)
{
	mNoisePtr = noise;
}

void FBmTexture::SetColor(const RGBColor& col)
{
	mColor = col;
}

void FBmTexture::SetMinValue(float value)
{
	mMinValue = value;
	mNoisePtr->SetfBmMin(value);
}

void FBmTexture::SetMaxValue(float value)
{
	mMaxValue = value;
	mNoisePtr->SetfBmMax(value);
}
