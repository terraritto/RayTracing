//mathmetics
#include "../Maths/Constants.h"
#include "../Maths/Vector3D.h"
#include "../Maths/Point3D.h"
#include "../Maths/Point2D.h"
#include "../Maths/Normal.h"
#include "../Maths/Ray.h"
//Object
#include "../Objects/Plane.h"
//Tracer
#include "../Tracer/MultipleObjects.h"
//Utility
#include "World.h"
//Sampler
#include "../Sampler/PureRandom.h"
#include "../Sampler/Regular.h"
#include "../Sampler/Jittered.h"
#include "../Sampler/MultiJittered.h"
#include "../Sampler/Hammersley.h"
#include "../Sampler/NRooks.h"
//Camera
#include "..//Cameras//Orthographic.h"
#include "..//Cameras//Pinhole.h"
#include "..//Cameras//ThinLens.h"
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
	int numSamples = 2;

	//set View Plane
	mViewPlane.SetHRes(1000);
	mViewPlane.SetVRes(1000);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = black;

	//set Tracer
	mTracerPtr = std::make_shared<MultipleObjects>(this);
	

	//set camera
	/*pinhole
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(1500, 0, 0);
	pinholePtr->SetLookAt(0, 0, 0);
	pinholePtr->SetViewDistance(400);
	pinholePtr->SetZoom(1.0);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);
	*/
	
	/* ortho
	std::shared_ptr<Orthographic> orthoPtr = std::make_shared<Orthographic>();
	orthoPtr->SetZWindow(500);
	SetCamera(orthoPtr);
	*/

	/*ThinLens*/
	std::shared_ptr<ThinLens> thinLensPtr = std::make_shared<ThinLens>();
	thinLensPtr->SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	thinLensPtr->SetEye(500, 0, 0);
	thinLensPtr->SetLookAt(0, 0, 0);
	thinLensPtr->SetFocalLength(500.0f);
	thinLensPtr->SetViewDistance(250.0f);
	thinLensPtr->ComputeUVW();
	SetCamera(thinLensPtr);

	//set object
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->SetCenter(0, 0, 0);
	sphere->SetRadius(250.0);
	sphere->SetColor(RGBColor(1, 1, 0));
	AddObject(sphere);

	sphere = std::make_shared<Sphere>();
	sphere->SetCenter(-100, 0, 500);
	sphere->SetRadius(100.0);
	sphere->SetColor(RGBColor(1, 0, 0));
	AddObject(sphere);
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

//specific camera
void World::SetCamera(std::shared_ptr<Camera> camera)
{
	if (mCameraPtr)
	{
		mCameraPtr.reset();
		mCameraPtr = nullptr;
	}

	mCameraPtr = camera;
}