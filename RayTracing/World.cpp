#include "Constants.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "World.h"
#include "SingleSphere.h"

World::World()
	: mBackGroundColor(black)
	, mTracerPtr(nullptr)
	, mViewPlane()
	, mSphere()
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
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetGamma(1.0);

	mBackGroundColor = black;
	mTracerPtr = std::make_shared<SingleSphere>(this);

	mSphere.SetCenter(0.0);
	mSphere.SetRadius(85.0);
}