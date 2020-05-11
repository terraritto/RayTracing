#include "PathTrace.h"

PathTrace::PathTrace(World* world)
	: Tracer(world)
{
}

PathTrace::~PathTrace()
{
}

RGBColor PathTrace::TraceRay(const Ray ray, const int depth) const
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

			return sr.mMaterialPtr->PathShade(sr);
		}
		else
		{
			return mWorld->mBackGroundColor;
		}
	}
}
