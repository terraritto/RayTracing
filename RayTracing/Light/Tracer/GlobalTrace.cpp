#include "GlobalTrace.h"

GlobalTrace::GlobalTrace(World* world)
	: Tracer(world)
{
}

GlobalTrace::~GlobalTrace()
{
}

RGBColor GlobalTrace::TraceRay(const Ray ray, const int depth) const
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

			return sr.mMaterialPtr->GlobalShade(sr);
		}
		else
		{
			return mWorld->mBackGroundColor;
		}
	}
}
