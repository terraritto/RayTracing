#include "Image.h"
#include "DxLib.h"
#include <fstream>
#include <sstream>

void Image::ReadPpmFile(std::string fileName)
{
	// read image
	int imageHandle = LoadSoftImage(fileName.c_str());

	// get image size
	GetSoftImageSize(imageHandle, &mHres, &mVres);
	
	//set vector size
	mPixel.resize(mHres);
	for (auto& pix : mPixel)
	{
		pix.resize(mVres);
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
		}
	}

	//delete image
	DeleteSoftImage(imageHandle);
}

RGBColor Image::GetColor(int row, int column)
{
	return mPixel[row][column];
}
