//mathmetics
#include "../Maths/Constants.h"
#include "../Maths/Vector3D.h"
#include "../Maths/Point3D.h"
#include "../Maths/Point2D.h"
#include "../Maths/Normal.h"
#include "../Maths/Ray.h"
//Object
#include "../Objects/Plane.h"
#include "../Objects/Sphere.h"
//Tracer
#include "../Tracer/MultipleObjects.h"
#include "../Tracer/RayCast.h"
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
#include "..//Cameras//FishEye.h"
#include "..//Cameras//Spherical.h"
#include "..//Cameras//StereoCamera.h"
//Light
#include "../Light/Ambient.h"
#include "../Light/Directional.h"
#include "../Light/PointLight.h"
//Material
#include "../Material/Matte.h"
//DX library
#include "DxLib.h"
//STL
#include <random>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

World::World()
	: mBackGroundColor(black)
	, mTracerPtr(nullptr)
	, mViewPlane()
	, mAmbientPtr(nullptr)
	, mCount(0)
{

}

World::~World()
{
	mTracerPtr.reset();
}

void World::Build()
{
	int numSamples = 10;

	//set View Plane
	mViewPlane.SetHRes(500);
	mViewPlane.SetVRes(500);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = black;

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);
	
	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(1.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(0, 0, 200);
	pinholePtr->SetLookAt(-5, 0, 0);
	pinholePtr->SetViewDistance(850.0);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Light
	std::shared_ptr<PointLight> lightPtr = std::make_shared<PointLight>();
	lightPtr->SetLocation(100, 50, 150);
	lightPtr->SetScaleRadiance(5.0);
	AddLight(lightPtr);
	
	/*
	std::shared_ptr<Directional> lightPtr = std::make_shared<Directional>();
	lightPtr->SetDirection(1, 1, 0);
	lightPtr->SetScaleRadiance(4.0);
	AddLight(lightPtr);
	*/
	//set object
	std::shared_ptr<Matte> mattePtr1 = std::make_shared<Matte>();
	mattePtr1->SetKa(0.25);
	mattePtr1->SetKd(0.65);
	mattePtr1->SetCd(1, 1, 0);
	std::shared_ptr<Sphere> spherePtr1 = std::make_shared<Sphere>(Point3D(10,-5,0), 27);
	spherePtr1->SetMaterial(mattePtr1);
	AddObject(spherePtr1);

	std::shared_ptr<Matte> mattePtr2 = std::make_shared<Matte>();
	mattePtr2->SetKa(0.15);
	mattePtr2->SetKd(0.85);
	mattePtr2->SetCd(0.71, 0.40, 0.16);
	std::shared_ptr<Sphere> spherePtr2 = std::make_shared<Sphere>(Point3D(-25, 10, -35), 27);
	spherePtr2->SetMaterial(mattePtr2);
	AddObject(spherePtr2);

	std::shared_ptr<Matte> mattePtr3 = std::make_shared<Matte>();
	mattePtr3->SetKa(0.15);
	mattePtr3->SetKd(0.5);
	mattePtr3->SetCd(0, 0.4, 0.2);
	std::shared_ptr<Plane> planePtr = std::make_shared<Plane>(Point3D(0, 0, -50), Normal(0,0,1));
	planePtr->SetMaterial(mattePtr3);
	AddObject(planePtr);
}

void World::AddObject(std::shared_ptr<GeometricObject> objectPtr)
{
	mObjects.emplace_back(objectPtr);
}

void World::AddLight(std::shared_ptr<Light> lightPtr)
{
	mLights.emplace_back(lightPtr);
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

ShadeRec World::HitObjects(const Ray& ray) 
{
	ShadeRec sr(*this);
	double t;
	Normal normal;
	Point3D localHitPoint;
	float tMin = kHugeValue;
	int numObjects = mObjects.size();

	for (int j = 0; j < numObjects; j++)
	{
		if (mObjects[j]->hit(ray, t, sr) && (t < tMin))
		{
			sr.mHitAnObject = true;
			tMin = t;
			sr.mMaterialPtr = mObjects[j]->GetMaterial();
			sr.mHitPoint = ray.mOrigin + t * ray.mDirection;
			normal = sr.mNormal;
			localHitPoint = sr.mLocalHitPoint;
		}
	}

	if (sr.mHitAnObject)
	{
		sr.mT = tMin;
		sr.mNormal = normal;
		sr.mLocalHitPoint = localHitPoint;
	}

	//display
	if (mCount > 100000)
	{
		ScreenFlip();
		mCount = 0;
	}
	mCount++;

	return sr;
}


void World::OpenWindow(const int hres, const int vres) const
{
	ChangeWindowMode(TRUE);
	SetGraphMode(hres, vres, 32);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	WaitKey();
}

void World::DisplayPixel(const int row, const int column, const RGBColor& rawColor) const
{
	RGBColor mappedColor;

	if (mViewPlane.mIsShowOutOfGamut)
	{
		mappedColor = ClampToColor(rawColor);
	}
	else
	{
		mappedColor = MaxToOne(rawColor);
	}

	if (mViewPlane.mGamma != 1.0)
	{
		mappedColor = mappedColor.PowColor(mViewPlane.mInvGamma);
	}

	//covert coordinate about y.
	int x = column;
	int y = mViewPlane.mVRes - row - 1;

	DrawPixel(x, y, GetColor(mappedColor.mRed * 255, mappedColor.mGreen * 255, mappedColor.mBlue * 255));
}

RGBColor World::MaxToOne(const RGBColor& c) const
{
	float maxValue = std::max<float>(c.mRed, std::max<float>(c.mBlue, c.mGreen));

	if (maxValue > 1.0)
	{
		return (c / maxValue);
	}
	else
	{
		return c;
	}
}

RGBColor World::ClampToColor(const RGBColor& raw) const
{
	RGBColor c(raw);
	if (raw.mRed > 1.0 || raw.mGreen > 1.0 || raw.mBlue > 1.0)
	{
		c.mRed = 1.0; c.mGreen = 0.0; c.mBlue = 0.0;
	}

	return c;
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

void World::SetAmbientLight(std::shared_ptr<Light> light)
{
	if (mAmbientPtr)
	{
		mAmbientPtr.reset();
		mAmbientPtr = nullptr;
	}

	mAmbientPtr = light;
}
