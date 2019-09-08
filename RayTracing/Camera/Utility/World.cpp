//mathmetics
#include "../Maths/Constants.h"
#include "../Maths/Vector3D.h"
#include "../Maths/Point3D.h"
#include "../Maths/Point2D.h"
#include "../Maths/Normal.h"
#include "../Maths/Ray.h"
//Object
#include "../Objects/Plane.h"
#include "../Objects/MultipleObjects.h"
//Utility
#include "World.h"
//Sampler
#include "../Sampler/PureRandom.h"
#include "../Sampler/Regular.h"
#include "../Sampler/Jittered.h"
#include "../Sampler/MultiJittered.h"
#include "../Sampler/Hammersley.h"
#include "../Sampler/NRooks.h"
//DX library
#include "DxLib.h"
//STL
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
	int numSamples = 25;

	mViewPlane.SetHRes(200);
	mViewPlane.SetVRes(200);
	mViewPlane.SetSampler(std::move(std::make_shared<Hammersley>(numSamples)));

	mBackGroundColor = black;
	mTracerPtr = std::make_shared<MultipleObjects>(this);

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->SetCenter(0, 0, 0);
	sphere->SetRadius(85.0);
	sphere->SetColor(RGBColor(1, 1, 0));
	AddObject(sphere);
}

void World::RenderScene() const
{
	RGBColor pixelColor;
	Ray ray;
	double zw = 100.0;
	int n = static_cast<int>(sqrt(mViewPlane.mNumSamples));
	Point2D pp; // sample point in [0,1] x [0,1]
	Point2D sp; // sample point on a pixel

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

			for (int j = 0; j < mViewPlane.mNumSamples; j++)
			{
				sp = mViewPlane.mSamplerPtr->SampleUnitSquare();
				pp.mPosX = mViewPlane.mPixelSize * (c - 0.5 * mViewPlane.mHRes + sp.mPosX);
				pp.mPosY = mViewPlane.mPixelSize * (r - 0.5 * mViewPlane.mVRes + sp.mPosY);
				ray.mOrigin = Point3D(pp.mPosX, pp.mPosY, zw);
				pixelColor += mTracerPtr->TraceRay(ray);
			}

			pixelColor /= mViewPlane.mNumSamples;
			DisplayPixel(r, c, pixelColor);
		}
	}
	WaitTimer(10000);
}

//render perspective ver.
//if use it, you must set appropriate values about eye and d.
void World::RenderPerspective() const
{
	RGBColor pixelColor;
	Ray ray;

	//Perspective-specific
	double eye = 100;
	double d = -100;

	OpenWindow(mViewPlane.mHRes, mViewPlane.mVRes); //pixelsize = 1.0,so don't have to mult pixelSize;
	ray.mOrigin = Point3D(0.0, 0.0, eye);

	for (int r = 0; r < mViewPlane.mVRes; r++) //up
	{
		for (int c = 0; c <= mViewPlane.mHRes; c++) //across
		{
			ray.mDirection = Vector3D(
				mViewPlane.mPixelSize * (c - 0.5 * (mViewPlane.mHRes - 1.0)),
				mViewPlane.mPixelSize * (r - 0.5 * (mViewPlane.mVRes - 1.0)),
				-d
			);
			ray.mDirection.Normalize();
			pixelColor = mTracerPtr->TraceRay(ray);
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