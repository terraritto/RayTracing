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
#include "../Material/CookTorrance.h"
#include "../Material/Plastic.h"
#include "../Material/Emissive.h"
#include "../Material/Reflective.h"
#include "../Material/GlossyReflector.h"
#include "../Material/Transparent.h"
#include "../Material/Dielectric.h"
#include "../Material/SV_Matte.h"
//Texture
#include "../Texture/Image.h"
#include "../Texture/ImageTexture.h"
#include "../Texture/Checker3D.h"
#include "../Texture/PlaneChecker.h"
#include "../Texture/FBmTexture.h"
#include "../Texture/WrappedFBmTexture.h"
#include "../Texture/RampFBmTexture.h"
//Noise
#include "../Noise/CubicNoise.h"
#include "../Noise/LinearNoise.h"
//Mapping
#include "../Mapping/RectangularMap.h"
#include "../Mapping/CylindricalMap.h"
#include "../Mapping/SphericalMap.h"
#include "../Mapping/LightProbeMap.h"
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
	ChangeWindowMode(TRUE);
	SetGraphMode(100, 100, 32);
	DxLib_Init();

}

World::~World()
{
	mTracerPtr.reset();
}

void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = RGBColor(0.0, 0.6588, 1.0);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.5);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(7.5, 4, 10);
	pinholePtr->SetLookAt(-1, 3.7, 0);
	pinholePtr->SetViewDistance(340);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Light
	std::shared_ptr<Directional> lightPtr = std::make_shared<Directional>();
	lightPtr->SetDirection(15, 15, 2.5);
	lightPtr->SetScaleRadiance(3.0);
	lightPtr->SetIsShadow(true);
	AddLight(lightPtr);
	
	/*
	std::shared_ptr<PointLight> lightPtr2 = std::make_shared<PointLight>();
	lightPtr2->SetLocation(15, 15, 2.5);
	lightPtr2->SetScaleRadiance(2.0);
	lightPtr2->SetIsShadow(true);
	AddLight(lightPtr2);

	//std::shared_ptr<Directional> lightPtr3 = std::make_shared<Directional>();
	//lightPtr3->SetDirection(1, 1, 0);
	//lightPtr3->SetScaleRadiance(4.0);
	//AddLight(lightPtr3);
	*/

	//set object
	std::shared_ptr<CookTorrance> mattePtr1 = std::make_shared<CookTorrance>();
	mattePtr1->SetKa(0.25);
	mattePtr1->SetKd(0.75);
	mattePtr1->SetKs(0.25);
	mattePtr1->SetAlpha(0.9);
	mattePtr1->SetFresnel(0.5);
	mattePtr1->SetCd(1, 1, 0);
	mattePtr1->SetCs(0.2);

	std::shared_ptr<Sphere> spherePtr1 = std::make_shared<Sphere>(Point3D(3.85, 2.3, -2.55), 2.3);
	spherePtr1->SetMaterial(mattePtr1);
	AddObject(spherePtr1);

	std::shared_ptr<CookTorrance> mattePtr2 = std::make_shared<CookTorrance>();
	mattePtr2->SetKa(0.45);
	mattePtr2->SetKd(0.75);
	mattePtr2->SetKs(0.25);
	mattePtr2->SetFresnel(0.5);
	mattePtr2->SetAlpha(0.85);
	mattePtr2->SetCd(0.75, 0.25, 0);
	mattePtr2->SetCs(0.2);
	std::shared_ptr<Sphere> spherePtr2 = std::make_shared<Sphere>(Point3D(-0.7, 1, 4.2), 2);
	spherePtr2->SetMaterial(mattePtr2);
	AddObject(spherePtr2);

	std::shared_ptr<Matte> mattePtr3 = std::make_shared<Matte>();
	mattePtr3->SetKa(0.15);
	mattePtr3->SetKd(0.5);
	mattePtr3->SetCd(0, 0.4, 0.2);
	std::shared_ptr<Plane> planePtr = std::make_shared<Plane>(Point3D(0, 0, 0), Normal(0,1,0));
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

	return sr;
}


void World::OpenWindow(const int hres, const int vres) const
{
	ChangeWindowMode(TRUE);
	SetGraphMode(hres, vres, 32);
	//DxLib_Init();
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
