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
#include "../Objects/Rectangle.h"
#include "../Objects/Box.h"
#include "../Objects/ConcaveSphere.h"
//Tracer
#include "../Tracer/MultipleObjects.h"
#include "../Tracer/RayCast.h"
#include "../Tracer/AreaLights.h"
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
#include "../Light/AmbientOccluder.h"
#include "../Light/Directional.h"
#include "../Light/PointLight.h"
#include "../Light/AreaLight.h"
#include "../Light/EnvironmentLight.h"
//Material
#include "../Material/Matte.h"
#include "../Material/Phong.h"
#include "../Material/Plastic.h"
#include "../Material/Emissive.h"
//BRDF
#include "../BRDF/GlossySpecular.h"
#include "../BRDF/Lambertian.h"
//DX library
#include "DxLib.h"
//STL
#include <random>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <numeric>

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
	int numSamples = 100;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = RGBColor(0.5);

	//set Tracer
	mTracerPtr = std::make_shared<AreaLights>(this);

	//Main Light
	std::shared_ptr<MultiJittered> samplePtr = std::make_shared<MultiJittered>(numSamples);
	
	
	std::shared_ptr<AmbientOccluder> ambientPtr = std::make_shared<AmbientOccluder>();
	ambientPtr->SetRadiance(1.0);
	ambientPtr->SetColor(white);
	ambientPtr->SetMinAmount(0.5);
	ambientPtr->SetSampler(samplePtr);
	SetAmbientLight(ambientPtr); //for(A) & (C)
	
	
	/*
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);
	*/

	//Add Light
	std::shared_ptr<Emissive> emissivePtr = std::make_shared<Emissive>();
	emissivePtr->SetLadiance(0.9);
	emissivePtr->SetCe(white);

	std::shared_ptr<ConcaveSphere> sphere_ptr = std::make_shared<ConcaveSphere>();
	sphere_ptr->SetRadius(1000000.0);
	sphere_ptr->SetMaterial(emissivePtr);
	sphere_ptr->SetIsShadow(false);
	AddObject(sphere_ptr);

	std::shared_ptr<EnvironmentLight> environmentLightPtr = std::make_shared<EnvironmentLight>();
	environmentLightPtr->SetMaterial(emissivePtr);
	environmentLightPtr->SetSampler(samplePtr->Clone());
	environmentLightPtr->SetIsShadow(true);
	AddLight(environmentLightPtr);
	
	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(100,45,100);
	pinholePtr->SetLookAt(-10,40,0);
	pinholePtr->SetViewDistance(400);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	float ka = 0.2;
	float ks = 1.0;
	float exp = 10.0;
	RGBColor cs(1, 0, 0);
	//large sphere
	std::shared_ptr<Phong> phong_ptr1 = std::make_shared<Phong>();
	phong_ptr1->SetKa(ka);
	phong_ptr1->SetKd(0.60);
	phong_ptr1->SetCd(0.75);
	phong_ptr1->SetKs(ks);
	phong_ptr1->SetExp(exp);
	phong_ptr1->SetCs(cs);

	std::shared_ptr<Sphere> sphere_ptr1 = std::make_shared<Sphere>(Point3D(38, 20, -24), 20);
	sphere_ptr1->SetMaterial(phong_ptr1);
	AddObject(sphere_ptr1);

	//small sphere
	std::shared_ptr<Phong> phong_ptr2 = std::make_shared<Phong>();
	phong_ptr2->SetKa(ka);
	phong_ptr2->SetKd(0.50);
	phong_ptr2->SetCd(0.95);
	phong_ptr2->SetKs(ks);
	phong_ptr2->SetExp(exp);
	phong_ptr2->SetCs(cs);

	std::shared_ptr<Sphere> sphere_ptr2 = std::make_shared<Sphere>(Point3D(34, 12, 13), 12);
	sphere_ptr2->SetMaterial(phong_ptr2);
	AddObject(sphere_ptr2);

	//medium sphere
	std::shared_ptr<Phong> phong_ptr3 = std::make_shared<Phong>();
	phong_ptr3->SetKa(ka);
	phong_ptr3->SetKd(0.50);
	phong_ptr3->SetCd(0.75);
	phong_ptr3->SetKs(ks);
	phong_ptr3->SetExp(exp);
	phong_ptr3->SetCs(cs);

	std::shared_ptr<Sphere> sphere_ptr3 = std::make_shared<Sphere>(Point3D(-7, 15, 42), 16);
	sphere_ptr3->SetMaterial(phong_ptr3);
	AddObject(sphere_ptr3);

	// box
	std::shared_ptr<Phong> phong_ptr5 = std::make_shared<Phong>();
	phong_ptr5->SetKa(ka);
	phong_ptr5->SetKd(0.50);
	phong_ptr5->SetCd(0.95);
	phong_ptr5->SetKs(ks);
	phong_ptr5->SetExp(exp);
	phong_ptr5->SetCs(cs);

	std::shared_ptr<Box> box_ptr = std::make_shared<Box>(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->SetMaterial(phong_ptr5);
	AddObject(box_ptr);

	// ground plane
	std::shared_ptr<Matte> matte_ptr6 = std::make_shared<Matte>();
	matte_ptr6->SetKa(0.15);
	matte_ptr6->SetKd(0.5);
	matte_ptr6->SetCd(0.7);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr6);
	AddObject(plane_ptr);
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
	/*
	if (mCount > 1000000000)
	{
		ScreenFlip();
		mCount = 0;
	}
	mCount++;
	*/

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
	/*
	if(c.mBlue == std::numeric_limits<float>::infinity())
	{
		maxValue = 0;
	}

	if (c.mRed == std::numeric_limits<float>::infinity())
	{
		maxValue = 0;
	}

	if (c.mGreen == std::numeric_limits<float>::infinity())
	{
		maxValue = 0;
	}
	*/

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
