#include "Constants.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Point2D.h"
#include "Normal.h"
#include "Ray.h"
#include "Plane.h"
#include "World.h"
#include "MultipleObjects.h"
#include "DxLib.h"
#include <random>
#include <stdlib.h>
#include <stdio.h>

World::World()
	: mBackGroundColor(black)
	, mTracerPtr(nullptr)
	, mViewPlane()
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
	mViewPlane.SetSamples(16);

	mBackGroundColor = black;
	mTracerPtr = std::make_shared<MultipleObjects>(this);

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->SetCenter(0, 0, 0);
	sphere->SetRadius(85.0);
	sphere->SetColor(RGBColor(1, 1, 0));
	AddObject(sphere);
}

//-----Regular Sampling-----
/*
void World::RenderScene() const
{
	RGBColor pixelColor;
	Ray ray;
	double zw = 100.0;
	int n = static_cast<int>(sqrt(mViewPlane.mNumSamples));
	Point2D pp;
	
	OpenWindow(mViewPlane.mHRes, mViewPlane.mVRes); //pixelsize = 1.0,so don't have to mult pixelSize;
	ray.mDirection = Vector3D(0, 0, -1);

	for (int r = 0; r < mViewPlane.mVRes; r++) //up
	{
		for (int c = 0; c <= mViewPlane.mHRes; c++) //across
		{
			pixelColor = black;
			
			for (int p = 0; p < n; p++)
			{
				for (int q = 0; q < n; q++)
				{
					pp.mPosX = mViewPlane.mPixelSize * (c - 0.5 * mViewPlane.mHRes + (q + 0.5) / n);
					pp.mPosY = mViewPlane.mPixelSize * (r - 0.5 * mViewPlane.mVRes + (p + 0.5) / n);
					ray.mOrigin = Point3D(pp.mPosX, pp.mPosY, zw);
					pixelColor += mTracerPtr->TraceRay(ray);
				}
			}
			
			pixelColor /= mViewPlane.mNumSamples;
			DisplayPixel(r, c, pixelColor);
		}
	}
	WaitTimer(10000);
}
*/

//Random Sampling
void World::RenderScene() const
{
	RGBColor pixelColor;
	Ray ray;
	double zw = 100.0;
	int n = static_cast<int>(sqrt(mViewPlane.mNumSamples));
	Point2D pp;

	OpenWindow(mViewPlane.mHRes, mViewPlane.mVRes); //pixelsize = 1.0,so don't have to mult pixelSize;
	ray.mDirection = Vector3D(0, 0, -1);

	//random
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, 1.0f);

	for (int r = 0; r < mViewPlane.mVRes; r++) //up
	{
		for (int c = 0; c <= mViewPlane.mHRes; c++) //across
		{
			pixelColor = black;

			for (int p = 0; p < n; p++)
			{
				pp.mPosX = mViewPlane.mPixelSize * (c - 0.5 * mViewPlane.mHRes + floatRand(mt));
				pp.mPosY = mViewPlane.mPixelSize * (r - 0.5 * mViewPlane.mVRes + floatRand(mt));
				ray.mOrigin = Point3D(pp.mPosX, pp.mPosY, zw);
				pixelColor += mTracerPtr->TraceRay(ray);
			}

			pixelColor /= n;
			DisplayPixel(r, c, pixelColor);
		}
	}
	WaitTimer(10000);
}

void World::AddObject(std::shared_ptr<GeometricObject> objectPtr)
{
	mObjects.emplace_back(objectPtr);
}

ShadeRec World::HitBareBonesObjects(const Ray& ray)
{
	ShadeRec sr(*this);
	double t;
	double tMin = kHugeValue;
	int numObjects = mObjects.size();

	for (int i = 0; i < numObjects; i++)
	{
		if (mObjects[i]->hit(ray, t, sr) && (t < tMin))
		{
			sr.mHitAnObject = true;
			tMin = t;
			sr.mColor = mObjects[i]->GetColor();
		}
	}

	return (sr);
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

	if (mViewPlane.mGamma != 1.0)
	{
		mappedColor = mappedColor.PowColor(mViewPlane.mInvGamma);
	}

	//covert coordinate about y.
	int x = column;
	int y = mViewPlane.mVRes - row - 1;

	DrawPixel(x, y, GetColor(rawColor.mRed *255, rawColor.mGreen * 255, rawColor.mBlue * 255));
}