#include "RampFBmTexture.h"

RampFBmTexture::RampFBmTexture()
	: mNoisePtr(nullptr)
	, mRampPtr(nullptr)
	, mAmount(0.0f)
{
}

RampFBmTexture::~RampFBmTexture()
{
}

// routine
/*
RGBColor RampFBmTexture::GetColor(const ShadeRec& sr) const
{
	float y = sr.mLocalHitPoint.mPosY;
	float u = (1.0 + std::sin(y)) / 2.0;
	int row = 0;
	int column = u * (mRampPtr->mHres - 1);

	return mRampPtr->GetColor(row, column);
}
*/

RGBColor RampFBmTexture::GetColor(const ShadeRec& sr) const
{
	float noise = mNoisePtr->ValuefBm(sr.mLocalHitPoint);
	float y = sr.mLocalHitPoint.mPosY + mAmount * noise;
	float u = 0.5 * (1.0 + std::sin(y));
	int column = 0;
	int row = u * (mRampPtr->mHres - 1);

	return mRampPtr->GetColor(row, column);
}

void RampFBmTexture::SetNoise(std::shared_ptr<LatticeNoise> noise)
{
	mNoisePtr = noise;
}

void RampFBmTexture::SetImage(std::shared_ptr<Image> image)
{
	mRampPtr = image;
}

void RampFBmTexture::SetAmount(float amount)
{
	mAmount = amount;
}
