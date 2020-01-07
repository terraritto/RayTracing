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
