#include "ToonImageTexture.h"

ToonImageTexture::ToonImageTexture()
{
}

ToonImageTexture::~ToonImageTexture()
{
}

void ToonImageTexture::SetImage(std::shared_ptr<AlphaImage> image)
{
	mImage = image;
}

void ToonImageTexture::SetMapping(std::shared_ptr<Mapping> map)
{
	mMapping = map;
}

RGBColor ToonImageTexture::GetToon(const float f) const
{
	int row, column;

	row = 0;
	column = static_cast<int>((mImage->mVres - 1) * f);

	return mImage->GetColor(row, column);
}
