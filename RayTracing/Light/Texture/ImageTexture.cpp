#include "ImageTexture.h"

ImageTexture::ImageTexture()
	: mMapping(nullptr)
	, mImage(nullptr)
{
}

ImageTexture::~ImageTexture()
{
}

void ImageTexture::SetImage(std::shared_ptr<Image> image)
{
	mImage = image;
}

void ImageTexture::SetMapping(std::shared_ptr<Mapping> map)
{
	mMapping = map;
}

RGBColor ImageTexture::GetColor(const ShadeRec& sr) const
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
		column = static_cast<int>(sr.mV *(mImage->mVres-1));
		row = static_cast<int>(sr.mU * (mImage->mHres-1));
	}
	
	return(mImage->GetColor(row,mImage->mVres - column-1));
}
