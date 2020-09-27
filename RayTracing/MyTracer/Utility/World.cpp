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
#include "../Material/MicrofasetReflective.h"
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
	, seed()
	, engine(seed())
	, dist(0.0,1.0)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(100, 100, 32);
	DxLib_Init();
}

World::~World()
{
	mTracerPtr.reset();
}

/*
void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(400);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(0);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);
	mBackGroundColor = RGBColor(0.5);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(1.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinhole_ptr = std::make_shared<Pinhole>();
	pinhole_ptr->SetEye(2, 3.5, 5);
	pinhole_ptr->SetLookAt(0);
	pinhole_ptr->SetViewDistance(800.0);
	pinhole_ptr->ComputeUVW();
	SetCamera(pinhole_ptr);

	//sub light
	std::shared_ptr<Directional> light_ptr1 = std::make_shared<Directional>();
	light_ptr1->SetDirection(14, 20, 25);
	light_ptr1->SetScaleRadiance(1.75);
	light_ptr1->SetIsShadow(true);
	AddLight(light_ptr1);

	//image
	std::shared_ptr<Image> image_ptr = std::make_shared<Image>();
	image_ptr->ReadPpmFile("Additional_Texture/TextureFiles/jpg/nwaka2.jpg");

	//mapping
	std::shared_ptr<CylindricalMap> map_ptr = std::make_shared<CylindricalMap>();

	// image texture
	std::shared_ptr<ImageTexture> texture_ptr = std::make_shared<ImageTexture>();
	texture_ptr->SetImage(image_ptr);
	texture_ptr->SetMapping(map_ptr);

	//set object
	std::shared_ptr<SV_Matte> sv_matte_ptr = std::make_shared<SV_Matte>();
	sv_matte_ptr->SetKa(0.40);
	sv_matte_ptr->SetKd(0.95);
	sv_matte_ptr->SetCd(texture_ptr);

	std::shared_ptr<OpenCylinder> cylinder_ptr = std::make_shared<OpenCylinder>();
	cylinder_ptr->SetMaterial(sv_matte_ptr);

	std::shared_ptr<Instance> lightlace_ptr = std::make_shared<Instance>(cylinder_ptr);
	lightlace_ptr->Scale(1.0, 1.0, 1.5);
	lightlace_ptr->RotateY(75);
	AddObject(lightlace_ptr);
}
*/

void World::Build()
{
	int numSamples = 5;

	//set View Plane
	mViewPlane.SetHRes(1920);
	mViewPlane.SetVRes(1080);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(10);

	mResult.resize(mViewPlane.mHRes);
	for (auto& res : mResult)
	{
		res.resize(mViewPlane.mVRes);
	}


	//set Tracer
	mTracerPtr = std::make_shared<AreaLights>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(1.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(77.6, 40.4, -80.0);
	pinholePtr->SetLookAt(77.6, 40.4, 0.0);
	pinholePtr->SetViewDistance(1000);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	Point3D p0;
	Vector3D a, b;
	Normal normal;

	// box dimension
	double width = 155.28;
	double height = 80.88;
	double depth = 55.92;

	// ceiling light
	std::shared_ptr<Emissive> emissive_ptr = std::make_shared<Emissive>();
	//emissive_ptr->SetCe(1.0, 1.0, 1.0);
	emissive_ptr->SetCe(1.0, 0.73, 0.4);
	emissive_ptr->SetLadiance(10);

	p0 = Point3D(width/4, height - 0.001, depth/4);
	a = Vector3D(0.0, 0.0, depth/2);
	b = Vector3D(width/2, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);

	//p0 = Point3D(0.0, 0.0, -depth * 2);
	//a = Vector3D(width, 0.0, 0.0);
	//b = Vector3D(0.0, height, 0.0);
	//normal = Normal(0.0, 0.0, 1.0);

	std::shared_ptr<Rectangler> light_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	light_ptr->SetMaterial(emissive_ptr);
	light_ptr->SetSampler(std::make_shared<MultiJittered>(numSamples));
	light_ptr->SetIsShadow(false);
	AddObject(light_ptr);

	std::shared_ptr<AreaLight> ceiling_light_ptr = std::make_shared<AreaLight>();
	ceiling_light_ptr->SetObject(light_ptr);
	ceiling_light_ptr->SetIsShadow(true);
	AddLight(ceiling_light_ptr);

	//front light
	p0 = Point3D(0.0, 0.0, -depth * 2);
	a = Vector3D(width, 0.0, 0.0);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(0.0, 0.0, 1.0);

	std::shared_ptr<Rectangler> light_ptr2 = std::make_shared<Rectangler>(p0, a, b, normal);
	light_ptr2->SetMaterial(emissive_ptr);
	light_ptr2->SetSampler(std::make_shared<MultiJittered>(numSamples));
	light_ptr2->SetIsShadow(false);
	AddObject(light_ptr);

	std::shared_ptr<AreaLight> front_light_ptr = std::make_shared<AreaLight>();
	front_light_ptr->SetObject(light_ptr2);
	front_light_ptr->SetIsShadow(true);
	AddLight(front_light_ptr);

	//point light
	auto light_ptr3 = std::make_shared<Directional>();
	light_ptr3->SetScaleRadiance(2.0);
	light_ptr3->SetColor(1.0, 0.73, 0.4);
	light_ptr3->SetDirection(0.0f, 0.0f, 1.0f);
	AddLight(light_ptr3);

	//object
	int modelHandle;
	std::string fileName = "Additional_File/MMD/Tda式初音ミクV4X_Ver1.00/Tda式初音ミク.pmx";
	//load and set model
	modelHandle = MV1LoadModel(fileName.c_str());
	MV1SetPosition(modelHandle, VGet(-width + width / 2, 0.0, depth / 4));
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));
	int attachIndex = MV1AttachAnim(modelHandle, 0, -1, FALSE);
	MV1SetAttachAnimTime(modelHandle, attachIndex, 0.0f);

	
	std::shared_ptr<Matte> mmd_matte = std::make_shared<Matte>();
	mmd_matte->SetKa(0.1);
	mmd_matte->SetKd(0.75);
	mmd_matte->SetCd(0.1, 0.5, 1.0);
	
	std::shared_ptr<Grid> mmd_ptr = std::make_shared<Grid>();
	mmd_ptr->SetShadowAlpha(*this); //for alpha shadow
	mmd_ptr->ReadMMDTriangles(modelHandle);
	//mmd_ptr->SetMaterial(mmd_matte);
	mmd_ptr->SetupCells();
	AddObject(mmd_ptr);

	MV1DeleteModel(modelHandle);

	//left wall
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.0);
	matte_ptr1->SetKd(0.6);
	matte_ptr1->SetCd(0.57, 0.025, 0.025);
	matte_ptr1->SetSamples(numSamples);

	p0 = Point3D(width, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(-1.0, 0.0, 0.0);
	std::shared_ptr<Rectangler> left_wall_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	left_wall_ptr->SetMaterial(matte_ptr1);
	AddObject(left_wall_ptr);

	//right wall
	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.0);
	matte_ptr2->SetKd(0.6);
	matte_ptr2->SetCd(0.37, 0.59, 0.2);
	matte_ptr2->SetSamples(numSamples);

	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(1.0, 0.0, 0.0);
	std::shared_ptr<Rectangler> right_wall_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	right_wall_ptr->SetMaterial(matte_ptr2);
	AddObject(right_wall_ptr);

	//back wall
	std::shared_ptr<Matte> matte_ptr3 = std::make_shared<Matte>();
	matte_ptr3->SetKa(0.0);
	matte_ptr3->SetKd(0.6);
	matte_ptr3->SetCd(1.0);
	matte_ptr3->SetSamples(numSamples);

	std::shared_ptr<Reflective> reflective_ptr = std::make_shared<Reflective>();
	reflective_ptr->SetKa(0);
	reflective_ptr->SetKd(0);
	reflective_ptr->SetCd(black);
	reflective_ptr->SetKs(0);
	reflective_ptr->SetKr(0.9);
	reflective_ptr->SetCr(0.9, 1.0, 0.9);

	p0 = Point3D(0.0, 0.0, depth);
	a = Vector3D(width, 0.0, 0.0);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(0.0, 0.0, -1.0);
	std::shared_ptr<Rectangler> back_wall_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	back_wall_ptr->SetMaterial(matte_ptr3);
	AddObject(back_wall_ptr);

	//floor
	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, 1.0, 0.0);
	std::shared_ptr<Rectangler> floor_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	floor_ptr->SetMaterial(matte_ptr3);
	AddObject(floor_ptr);

	//ceiling
	p0 = Point3D(0.0, height, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	std::shared_ptr<Rectangler> ceiling_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	ceiling_ptr->SetMaterial(matte_ptr3);
	AddObject(ceiling_ptr);
	
	//short box
	//top
	p0 = Point3D(13.0, 16.5, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(16.0, 0.0, 4.9);
	normal = Normal(0.0, 1.0, 0.0);
	std::shared_ptr<Rectangler> short_top_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	short_top_ptr->SetMaterial(matte_ptr3);
	AddObject(short_top_ptr);

	//side1
	p0 = Point3D(13.0, 0.0, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(0.0, 16.5, 0.0);
	std::shared_ptr<Rectangler> short_side_ptr1 = std::make_shared<Rectangler>(p0, a, b);
	short_side_ptr1->SetMaterial(matte_ptr3);
	AddObject(short_side_ptr1);

	//side2
	p0 = Point3D(8.2, 0.0, 22.5);
	a = Vector3D(15.8, 0.0, 4.7);
	std::shared_ptr<Rectangler> short_side_ptr2 = std::make_shared<Rectangler>(p0, a, b);
	short_side_ptr2->SetMaterial(matte_ptr3);
	AddObject(short_side_ptr2);

	//side3
	p0 = Point3D(24.2, 0.0, 27.4);
	a = Vector3D(4.8, 0.0, -16.0);
	std::shared_ptr<Rectangler> short_side_ptr3 = std::make_shared<Rectangler>(p0, a, b);
	short_side_ptr3->SetMaterial(matte_ptr3);
	AddObject(short_side_ptr3);

	//side4
	p0 = Point3D(29.0, 0.0, 11.4);
	a = Vector3D(-16.0, 0.0, -4.9);
	std::shared_ptr<Rectangler> short_side_ptr4 = std::make_shared<Rectangler>(p0, a, b);
	short_side_ptr4->SetMaterial(matte_ptr3);
	AddObject(short_side_ptr4);

	//tall
	//top
	p0 = Point3D(42.3, 33.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(4.9, 0.0, 15.9);
	normal = Normal(0.0, 1.0, 0.0);
	std::shared_ptr<Rectangler> tall_top_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	tall_top_ptr->SetMaterial(matte_ptr3);
	AddObject(tall_top_ptr);

	//side1
	p0 = Point3D(42.3, 0.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(0.0, 33.0, 0.0);
	std::shared_ptr<Rectangler> tall_side_ptr1 = std::make_shared<Rectangler>(p0, a, b);
	tall_side_ptr1->SetMaterial(matte_ptr3);
	AddObject(tall_side_ptr1);

	//side2
	p0 = Point3D(26.5, 0.0, 29.6);
	a = Vector3D(4.9, 0.0, 15.9);
	std::shared_ptr<Rectangler> tall_side_ptr2 = std::make_shared<Rectangler>(p0, a, b);
	tall_side_ptr2->SetMaterial(matte_ptr3);
	AddObject(tall_side_ptr2);

	//side3
	p0 = Point3D(31.4, 0.0, 45.5);
	a = Vector3D(15.8, 0.0, -4.9);
	std::shared_ptr<Rectangler> tall_side_ptr3 = std::make_shared<Rectangler>(p0, a, b);
	tall_side_ptr3->SetMaterial(matte_ptr3);
	AddObject(tall_side_ptr3);

	//side4
	p0 = Point3D(47.2, 0.0, 40.6);
	a = Vector3D(-4.9, 0.0, -15.9);
	std::shared_ptr<Rectangler> tall_side_ptr4 = std::make_shared<Rectangler>(p0, a, b);
	tall_side_ptr4->SetMaterial(matte_ptr3);
	AddObject(tall_side_ptr4);
	
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

void World::DisplayPixel(const int row, const int column, const RGBColor& rawColor) 
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

	mResult[x][y] = mappedColor;
	//DrawPixel(x, y, GetColor(mappedColor.mRed * 255, mappedColor.mGreen * 255, mappedColor.mBlue * 255));
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
