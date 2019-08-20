#include "MultipleObjects.h"
#include "World.h"

MultipleObjects::MultipleObjects()
	:Tracer()
{

}

MultipleObjects::MultipleObjects(World* worldPtr)
	: Tracer(worldPtr)
{

}

MultipleObjects::~MultipleObjects()
{

}

RGBColor MultipleObjects::TraceRay(const Ray& ray) const
{
	ShadeRec sr(mWorld->HitBareBonesObjects(ray));

	if (sr.mHitAnObject)
	{
		return sr.mColor;
	}
	else
	{
		return mWorld->mBackGroundColor;
	}
}