#include "Whitted.h"

Whitted::Whitted(World* world)
	: Tracer(world)
{
}

Whitted::~Whitted()
{
}

RGBColor Whitted::TraceRay(const Ray ray, const int depth) const
{
	if (depth > mWorld->mViewPlane.mMaxDepth)
	{
		return black;
	}
	else
	{
		ShadeRec sr(mWorld->HitObjects(ray));

		if (sr.mHitAnObject)
		{
			sr.mDepth = depth;
			sr.mRay = ray;
			return sr.mMaterialPtr->Shade(sr);
		}
		else
		{
			return mWorld->mBackGroundColor;
		}
	}
}

RGBColor Whitted::TraceRay(const Ray ray, float& tMin, const int depth) const
{
	if (depth > mWorld->mViewPlane.mMaxDepth)
	{
		tMin = kHugeValue;
		return black;
	}
	else
	{
		ShadeRec sr(mWorld->HitObjects(ray));
		if (sr.mHitAnObject)
		{
			sr.mDepth = depth;
			sr.mRay = ray;
			tMin = sr.mT;
			return sr.mMaterialPtr->Shade(sr);
		}
		else
		{
			tMin = kHugeValue;
			return mWorld->mBackGroundColor;
		}
	}
}
