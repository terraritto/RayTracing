#include "Constants.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "Plane.h"
#include "World.h"
#include "MultipleObjects.h"
#include "DxLib.h"

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
	mViewPlane.SetHRes(200);
	mViewPlane.SetVRes(200);

	mBackGroundColor = black;
	mTracerPtr = std::make_shared<MultipleObjects>(this);

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->SetCenter(0, -25, 0);
	sphere->SetRadius(80);
	sphere->SetColor(RGBColor(0, 0, 1));
	AddObject(sphere);

	sphere.reset();
	sphere = std::make_shared<Sphere>();
	sphere->SetCenter(-40, -50, 0);
	sphere->SetRadius(90);
	sphere->SetColor(RGBColor(0, 1, 0));
	AddObject(sphere);

	sphere.reset();
	sphere = std::make_shared<Sphere>();
	sphere->SetCenter(60, 130, 0);
	sphere->SetRadius(70);
	sphere->SetColor(RGBColor(0, 1, 1));
	AddObject(sphere);

	sphere.reset();
	sphere = std::make_shared<Sphere>(Point3D(0, 30, 0), 60);
	sphere->SetColor(RGBColor(1, 1, 0));
	AddObject(sphere);

	std::shared_ptr<Plane> plane = std::make_shared<Plane>(Point3D(0, 0, 0), Normal(0, 1, 1));
	plane->SetColor(RGBColor(0.3, 0.3, 0.3));
	AddObject(plane);
}

void World::RenderScene() const
{
	RGBColor pixelColor;
	Ray ray;
	double zw = 100.0;
	double x, y;
	
	OpenWindow(mViewPlane.mHRes, mViewPlane.mVRes); //pixelsize = 1.0,so don't have to mult pixelSize;
	ray.mDirection = Vector3D(0, 0, -1);

	for (int r = 0; r < mViewPlane.mVRes; r++) //up
	{
		for (int c = 0; c <= mViewPlane.mHRes; c++) //across
		{
			x = mViewPlane.mPixelSize * (c - 0.5 * (mViewPlane.mHRes - 1.0));
			y = mViewPlane.mPixelSize * (r - 0.5 * (mViewPlane.mVRes - 1.0));
			ray.mOrigin = Point3D(x, y, zw);
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