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
#include "../Tracer/Whitted.h"
#include "../Tracer/PathTrace.h"
#include "../Tracer/GlobalTrace.h"
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
#include "../Material/Reflective.h"
#include "../Material/GlossyReflector.h"
//BRDF
#include "../BRDF/GlossySpecular.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/PerrfectSpecular.h"
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
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(800);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(0);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);
	mBackGroundColor = white;

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(1.0);
	SetAmbientLight(ambientPtr);

	//sub Light
	std::shared_ptr<PointLight> light_ptr = std::make_shared<PointLight>();
	light_ptr->SetLocation(150, 500, 300);
	light_ptr->SetScaleRadiance(5.00);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	//Set Camera
	std::shared_ptr<Spherical> spherical_ptr = std::make_shared<Spherical>();
	spherical_ptr->SetEye(10, 15, 13);
	spherical_ptr->SetLookAt(34, 15, 0);
	spherical_ptr->SetPsiMax(180);
	spherical_ptr->SetLambdaMax(360);
	spherical_ptr->ComputeUVW();
	SetCamera(spherical_ptr);

	//set object
	float a = 10;
	float b = 12;
	int num_rows = 10;
	int num_columns = 12;
	float width = 7;
	float length = 7;
	float min_size = 6;
	float offset = 1.0;
	float min_height = 0.0;
	float max_height = 30;
	float height;
	int num_park_rows = 4;
	int num_park_columns = 6;
	int row_test;
	int column_test;
	float min_color = 0.1;
	float max_color = 0.9;

	//random
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, 1.0f);

	//grid
	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();

	for (int r = 0; r < num_rows; r++)
	{
		for (int c = 0; c < num_columns; c++)
		{
			if (r - num_rows / 2 >= 0)
			{
				row_test = r - num_rows / 2;
			}
			else
			{
				row_test = r - num_rows / 2 + 1;
			}

			if (c - num_columns / 2 >= 0)
			{
				column_test = c - num_columns / 2;
			}
			else
			{
				column_test = c - num_columns / 2 + 1;
			}

			if (std::abs(row_test) >= (num_park_rows / 2) || std::abs(column_test) >= (num_park_columns / 2))
			{
				std::shared_ptr<Matte> matte_ptr = std::make_shared<Matte>();
				matte_ptr->SetKa(0.4);
				matte_ptr->SetKd(0.6);
				matte_ptr->SetCd(
					min_color + floatRand(mt) * (max_color - min_color),
					min_color + floatRand(mt) * (max_color - min_color),
					min_color + floatRand(mt) * (max_color - min_color)
				);

				float xc = a * (r - num_rows / 2.0 + 0.5);
				float zc = b * (c - num_columns / 2.0 + 0.5);

				width = min_size + floatRand(mt) * (a - 2 * offset - min_size);
				length = min_size + floatRand(mt) * (b - 2 * offset - min_size);

				float xmin = xc - width / 2.0;
				float ymin = 0.0;
				float zmin = zc - length / 2.0;

				height = min_height + floatRand(mt) * (max_height - min_height);

				if (r == 1 || r == num_rows - 2 || c == 1 || c == num_columns - 2)
				{
					height *= 1.5;
				}

				float xmax = xc + width / 2.0;
				float ymax = height;
				float zmax = zc + length / 2.0;

				std::shared_ptr<Box> building_ptr = std::make_shared<Box>(Point3D(xmin, ymin, zmin), Point3D(xmax, ymax, zmax));
				building_ptr->SetMaterial(matte_ptr);
				grid_ptr->AddObject(building_ptr);
			}
		}
	}

	grid_ptr->SetupCells();
	AddObject(grid_ptr);

	//plane
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.3);
	matte_ptr1->SetKd(0.50);
	matte_ptr1->SetCd(0.3, 0.5, 0.3);

	std::shared_ptr<Box> park_ptr = std::make_shared<Box>(
		Point3D(-a * num_park_rows / 2, 0.0, -b * num_park_columns / 2),
		Point3D(a * num_park_rows / 2, 0.1, b * num_park_columns / 2)
		);
	park_ptr->SetMaterial(matte_ptr1);
	AddObject(park_ptr);

	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.3);
	matte_ptr2->SetKd(0.4);
	matte_ptr2->SetCd(white);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0, 0.01, 0), Normal(0, 1, 0));
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
