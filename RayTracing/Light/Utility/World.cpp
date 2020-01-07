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
#include "../Objects/Disk.h"
#include "../Objects/Box.h"
#include "../Objects/ConcaveSphere.h"
#include "../Objects/Triangle.h"
#include "../Objects/Torus.h"
#include "../Objects/OpenCylinder.h"
#include "../Objects/PartSphere.h"
#include "../Objects/SolidCylinder.h"
#include "../Objects/BeveledCylinder.h"
#include "../Objects/Instance.h"
#include "../Objects/Grid.h"
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
	int numSamples = 1;

	//set View Plane
	mViewPlane.SetHRes(500);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = black;

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);

	//Add Light
	std::shared_ptr<Directional> light_ptr = std::make_shared<Directional>();
	light_ptr->SetDirection(20,40,20);
	light_ptr->SetScaleRadiance(3.0);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	//set object
	const std::string fileName = "./Additional_File/PLYFiles/bunny/reconstruction/bun_zipper_res2.ply";
	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();
	grid_ptr->ReadTriangles(fileName, Grid::ETriangleType::flat);
	grid_ptr->SetupCells();

	int num_levels = 6;
	int instances_grid_res = 10;
	int delta = 0.1;
	int gap = 0.08;
	double size = 0.1;
	double mcx = 0.5;

	std::shared_ptr<Grid> current_grid_ptr = grid_ptr;

	//random
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, 1.0f);

	for (int level = 0; level < num_levels; level++)
	{
		std::shared_ptr<Grid> instance_grid_ptr = std::make_shared<Grid>();

		for (int i = 0; i < instances_grid_res; i++)
		{
			for (int k = 0; k < instances_grid_res; k++)
			{
				//set object
				std::shared_ptr<Phong> phong_ptr1 = std::make_shared<Phong>();
				phong_ptr1->SetKa(0.2);
				phong_ptr1->SetKd(0.5);
				phong_ptr1->SetCd(floatRand(mt),floatRand(mt),floatRand(mt));
				phong_ptr1->SetKs(0.4);
				phong_ptr1->SetExp(20);

				std::shared_ptr<Instance> instance_ptr = std::make_shared<Instance>();
				instance_ptr->SetObject(current_grid_ptr);
				instance_ptr->SetMaterial(phong_ptr1);
				instance_ptr->Translate(i * (size + gap), 0.0, k * (size + gap));
				instance_ptr->ComputeBoundingBox();
				instance_grid_ptr->AddObject(instance_ptr);
			}
		}
		size = instances_grid_res * size + (instances_grid_res - 1) * gap;
		gap = delta * size;
		instance_grid_ptr->SetupCells();
		current_grid_ptr = instance_grid_ptr;
	}
	AddObject(current_grid_ptr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(7 * mcx * size, 4 * mcx * size, 5 * mcx * size);
	pinholePtr->SetLookAt(mcx * size, 0.0, mcx * size);
	pinholePtr->SetViewDistance(300000000);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

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
