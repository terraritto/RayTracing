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
#include "..//Cameras//FishEye.h"
#include "..//Cameras//Spherical.h"
#include "..//Cameras//StereoCamera.h"
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
	int numSamples = 100;

	//set View Plane
	mViewPlane.SetHRes(300);
	mViewPlane.SetVRes(300);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = black;

	//set Tracer
	mTracerPtr = std::make_shared<MultipleObjects>(this);
	

	//set camera
	//implamented below camera
	/*
	pinhole camera
	orthographic camera
	thinlens camera
	fisheye camera
	spherical camera
	stereo camera
	*/

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

	/*ThinLens
	std::shared_ptr<ThinLens> thinLensPtr = std::make_shared<ThinLens>();
	thinLensPtr->SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	thinLensPtr->SetEye(500, 0, 0);
	thinLensPtr->SetLookAt(0, 0, 0);
	thinLensPtr->SetFocalLength(500.0f);
	thinLensPtr->SetViewDistance(250.0f);
	thinLensPtr->ComputeUVW();
	SetCamera(thinLensPtr);
	*/

	/*FishEye
	std::shared_ptr<FishEye> fishEyePtr = std::make_shared<FishEye>();
	fishEyePtr->SetEye(1500, 0, 0);
	fishEyePtr->SetLookAt(0, 0, 0);
	fishEyePtr->SetPsiMax(0);
	fishEyePtr->ComputeUVW();
	SetCamera(fishEyePtr);
	*/

	/*Spherical
	std::shared_ptr<Spherical> sphericalPtr = std::make_shared<Spherical>();
	sphericalPtr->SetEye(1500, 0, 0);
	sphericalPtr->SetLookAt(0, 0, 0);
	sphericalPtr->SetPsiMax(90);
	sphericalPtr->SetLambdaMax(180);
	sphericalPtr->ComputeUVW();
	SetCamera(sphericalPtr);
	*/
	
	/*StereoCamera*/
	float vpd = 400; // view plane distance

	std::shared_ptr<Pinhole> leftCameraPtr = std::make_shared<Pinhole>();
	leftCameraPtr->SetViewDistance(vpd);
	std::shared_ptr<Pinhole> rightCameraPtr = std::make_shared<Pinhole>();
	rightCameraPtr->SetViewDistance(vpd);

	std::shared_ptr<StereoCamera> stereoPtr = std::make_shared<StereoCamera>();
	stereoPtr->SetLeftCamera(leftCameraPtr);
	stereoPtr->SetRightCamera(rightCameraPtr);
	stereoPtr->UseParallelViewing();
	stereoPtr->SetPixelGap(5);
	stereoPtr->SetEye(1500, 0, 0);
	stereoPtr->SetLookAt(0);
	stereoPtr->ComputeUVW();
	stereoPtr->SetStereoAngle(10.0f);
	stereoPtr->SetupCameras();
	SetCamera(stereoPtr);
	
	//set object
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->SetCenter(0, 0, 0);
	sphere->SetRadius(50.0);
	sphere->SetColor(RGBColor(1, 1, 0));
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