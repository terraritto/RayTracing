#include "GlobalTrace.h"

GlobalTrace::GlobalTrace(World* world)
	: Tracer(world)
{
}

GlobalTrace::~GlobalTrace()
{
}

/*
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
*/

RGBColor GlobalTrace::TraceRay(const Ray ray, const int depth) const
{
	//get information
	ShadeRec sr(mWorld->HitObjects(ray));
	
	//isn't hit?
	if (!sr.mHitAnObject) { return mWorld->mBackGroundColor; }

	// probability for russian roulette
	double probability = std::max({ sr.mColor.mBlue, sr.mColor.mGreen, sr.mColor.mRed });

	// if reflect num > depth Max Limit
	// then rise rapidly probability(to take measures with stack overflow)
	if (depth > DEPTH_LIMIT)
	{
		probability *= std::pow(0.5, depth - DEPTH_LIMIT);
	}

	if (depth > mWorld->mViewPlane.mMaxDepth)
	{
		// 1-P_RR
		if (mWorld->dist(mWorld->engine) >= probability)
		{
			return black;
		}
	}
	else
	{
		// Gurantee ray bound num
		probability = 1.0;
	}

	// next ray(P_RR)
	sr.mDepth = depth;
	sr.mRay = ray;
	return sr.mMaterialPtr->GlobalShade(sr);

}

