#include "AreaLights.h"

AreaLights::AreaLights()
	: Tracer()
{
}

AreaLights::AreaLights(World* world)
	: Tracer(world)
{
}

AreaLights::~AreaLights()
{
}

RGBColor AreaLights::TraceRay(const Ray ray, const int depth) const
{
	if (depth > mWorld->mViewPlane.mMaxDepth)
	{
		return black;
	}
	else
	{

		ShadeRec sr(mWorld->HitObjects(ray)); //for multi thread

		if (sr.mHitAnObject)
		{
			sr.mRay = ray;
			sr.mDepth = depth;
			return sr.mMaterialPtr->AreaLightShade(sr);
		}
		else
		{
			return mWorld->mBackGroundColor;
		}
	}
}

RGBColor AreaLights::TraceRay(const Ray ray, float& tMin, const int depth) const
{
	if (depth > mWorld->mViewPlane.mMaxDepth)
	{
		tMin = kHugeValue;
		return black;
	}
	else
	{

		ShadeRec sr(mWorld->HitObjects(ray)); //for multi thread

		if (sr.mHitAnObject)
		{
			sr.mRay = ray;
			sr.mDepth = depth;
			tMin = sr.mT;
			return sr.mMaterialPtr->AreaLightShade(sr);
		}
		else
		{
			tMin = kHugeValue;
			return mWorld->mBackGroundColor;
		}
	}
}
