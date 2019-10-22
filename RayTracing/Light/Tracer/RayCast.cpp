#include "RayCast.h"

RayCast::RayCast()
	: Tracer()
{
}

RayCast::RayCast(World* world)
	: Tracer(world)
{
}

RayCast::~RayCast()
{
}

RGBColor RayCast::TraceRay(const Ray ray, const int depth) const
{
	ShadeRec sr(mWorld->HitObjects(ray));

	if (sr.mHitAnObject)
	{
		sr.mRay = ray;
		return sr.mMaterialPtr->Shade(sr);
	}
	else
	{
		return mWorld->mBackGroundColor;
	}
}
