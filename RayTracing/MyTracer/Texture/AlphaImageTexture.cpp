#include "AlphaImageTexture.h"

AlphaImageTexture::AlphaImageTexture()
{
}

AlphaImageTexture::~AlphaImageTexture()
{
}

void AlphaImageTexture::SetImage(std::shared_ptr<AlphaImage> image)
{
	mImage = image;
}

void AlphaImageTexture::SetMapping(std::shared_ptr<Mapping> map)
{
	mMapping = map;
}

RGBColor AlphaImageTexture::GetColor(const ShadeRec& sr) const
{
	int row, column;

	if (mMapping)
	{
		mMapping->GetTexelCoordinates(
			sr.mLocalHitPoint,
			mImage->mHres,
			mImage->mVres,
			row,
			column
		);
	}
	else
	{
		column = static_cast<int>(sr.mV * (mImage->mVres - 1));
		row = static_cast<int>(sr.mU * (mImage->mHres - 1));
	}

	return(mImage->GetColor(row, mImage->mVres - column - 1));
}

float AlphaImageTexture::GetAlpha(const ShadeRec& sr) const
{
	int row, column;
	column = static_cast<int>(sr.mV * (mImage->mVres - 1));
	row = static_cast<int>(sr.mU * (mImage->mHres - 1));

	return mImage->GetAlpha(row, mImage->mVres - column - 1);
}
