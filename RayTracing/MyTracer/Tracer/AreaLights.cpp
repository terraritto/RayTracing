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

		ShadeRec sr(mWorld->HitObjects(ray));

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
