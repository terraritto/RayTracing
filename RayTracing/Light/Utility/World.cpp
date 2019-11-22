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
	mViewPlane.SetVRes(600);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = RGBColor(0.5);

	//set Tracer
	mTracerPtr = std::make_shared<AreaLights>(this);

	//Main Light
	std::shared_ptr<MultiJittered> samplePtr = std::make_shared<MultiJittered>(numSamples);

	/*
	std::shared_ptr<AmbientOccluder> ambientPtr = std::make_shared<AmbientOccluder>();
	ambientPtr->SetRadiance(1.0);
	ambientPtr->SetColor(white);
	ambientPtr->SetMinAmount(0.0);
	ambientPtr->SetSampler(samplePtr);
	SetAmbientLight(ambientPtr);
	*/
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0);
	SetAmbientLight(ambientPtr);
	//Add Light
	float width = 4.0;
	float height = 4.0;
	Point3D center(0.0, 7.0, -7.0);
	Point3D p0(-0.5 * width, center.mPosY - 0.5 * height, center.mPosZ);
	Vector3D a(width, 0.0, 0.0);
	Vector3D b(0.0, height, 0.0);
	Normal normal(0, 0, 1);

	std::shared_ptr<Emissive> emissivePtr = std::make_shared<Emissive>();
	emissivePtr->SetLadiance(40.0);
	emissivePtr->SetCe(white);
	
	std::shared_ptr<Rectangler> rectanglePtr = std::make_shared<Rectangler>(p0, a, b, normal);
	rectanglePtr->SetMaterial(emissivePtr);
	rectanglePtr->SetSampler(samplePtr);
	rectanglePtr->SetIsShadow(false);
	AddObject(rectanglePtr);

	std::shared_ptr<AreaLight> areaLightPtr = std::make_shared<AreaLight>();
	areaLightPtr->SetObject(rectanglePtr);
	areaLightPtr->SetIsShadow(true);
	AddLight(areaLightPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(-20,10,20);
	pinholePtr->SetLookAt(0, 2, 0);
	pinholePtr->SetViewDistance(1080);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	float box_width = 1.0; 		// x dimension
	float box_depth = 1.0; 		// z dimension
	float box_height = 4.5; 		// y dimension
	float gap = 3.0;

	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.25);
	matte_ptr1->SetKd(0.75);
	matte_ptr1->SetCd(0.4, 0.7, 0.4);     // green

	std::shared_ptr<Box> box_ptr0 = std::make_shared<Box>(
		Point3D(-1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth),
		Point3D(-1.5 * gap - box_width, box_height, 0.5 * box_depth));
	box_ptr0->SetMaterial(matte_ptr1);
	AddObject(box_ptr0);

	std::shared_ptr<Box> box_ptr1 = std::make_shared<Box>(
		Point3D(-0.5 * gap - box_width, 0.0, -0.5 * box_depth),
		Point3D(-0.5 * gap, box_height, 0.5 * box_depth));
	box_ptr1->SetMaterial(matte_ptr1->Clone());
	AddObject(box_ptr1);

	std::shared_ptr<Box> box_ptr2 = std::make_shared<Box>(
		Point3D(0.5 * gap, 0.0, -0.5 * box_depth),
		Point3D(0.5 * gap + box_width, box_height, 0.5 * box_depth));
	box_ptr2->SetMaterial(matte_ptr1->Clone());
	AddObject(box_ptr2);

	std::shared_ptr<Box> box_ptr3 = std::make_shared<Box>(
		Point3D(1.5 * gap + box_width, 0.0, -0.5 * box_depth),
		Point3D(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
	box_ptr3->SetMaterial(matte_ptr1->Clone());
	AddObject(box_ptr3);

	// ground plane

	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.1);
	matte_ptr2->SetKd(0.9);
	matte_ptr2->SetCd(white);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr2);
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
