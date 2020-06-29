#include "AlphaImage.h"
#include "DxLib.h"

void AlphaImage::ReadPpmFile(std::string fileName)
{
	// read image
	int imageHandle = LoadSoftImage(fileName.c_str());

	// get image size
	GetSoftImageSize(imageHandle, &mHres, &mVres);

	//set vector size
	mPixel.resize(mHres);
	mAlpha.resize(mHres);
	for (auto& pix : mPixel)
	{
		pix.resize(mVres);
	}
	for (auto& al : mAlpha)
	{
		al.resize(mVres);
	}

	//set color
	for (int x = 0; x < mHres; x++)
	{
		for (int y = 0; y < mVres; y++)
		{
			int r, g, b, a;

			GetPixelSoftImage(imageHandle, x, y, &r, &g, &b, &a);
			mPixel[x][y].mRed = r / 255.0;
			mPixel[x][y].mGreen = g / 255.0;
			mPixel[x][y].mBlue = b / 255.0;
			mAlpha[x][y] = a / 255.0f < 0.0f || a/255.0f > 1.0f ? 1.0f : a / 255.0f;
		}
	}

	//delete image
	DeleteSoftImage(imageHandle);

}

RGBColor AlphaImage::GetColor(int row, int column)
{
	return mPixel[row][column] * mAlpha[row][column];
}

float AlphaImage::GetAlpha(int row, int column)
{
	return mAlpha[row][column];
}
