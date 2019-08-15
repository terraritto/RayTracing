#include "Constants.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "World.h"
#include "SingleSphere.h"
#include "DxLib.h"

World::World()
	: mBackGroundColor(black)
	, mTracerPtr(nullptr)
	, mViewPlane()
	, mSphere()
{

}

World::~World()
{
	mTracerPtr.reset();
}

void World::Build()
{
	mViewPlane.SetHRes(200);
	mViewPlane.SetVRes(200);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetGamma(1.0);

	mBackGroundColor = black;
	mTracerPtr = std::make_shared<SingleSphere>(this);

	mSphere.SetCenter(0.0);
	mSphere.SetRadius(85.0);
}

void World::RenderScene() const
{
	RGBColor pixelColor;
	Ray ray;
	double zw = 100.0;
	double x, y;
	
	OpenWindow(mViewPlane.mHRes, mViewPlane.mVRes); //pixelsize = 1.0,so don't have to mult pixelSize;
	ray.mDirection = Vector3D(0, 0, -1);

	for (int r = 0; r < mViewPlane.mVRes; r++) //up
	{
		for (int c = 0; c <= mViewPlane.mHRes; c++) //across
		{
			x = mViewPlane.mPixelSize * (c - 0.5 * (mViewPlane.mHRes - 1.0));
			y = mViewPlane.mPixelSize * (r - 0.5 * (mViewPlane.mVRes - 1.0));
			ray.mOrigin = Point3D(x, y, zw);
			pixelColor = mTracerPtr->TraceRay(ray);
			DisplayPixel(r, c, pixelColor);
		}
	}
	WaitTimer(10000);
}

void World::OpenWindow(const int hres, const int vres) const
{
	ChangeWindowMode(TRUE);
	SetGraphMode(hres, vres, 32);
	DxLib_Init();
}

void World::DisplayPixel(const int row, const int column, const RGBColor& rawColor) const
{
	RGBColor mappedColor;

	//covert coordinate about y.
	int x = column;
	int y = mViewPlane.mVRes - row - 1;

	DrawPixel(x, y, GetColor(rawColor.mRed *255, rawColor.mGreen * 255, rawColor.mBlue * 255));
}