#include "SingleSphere.h"
#include "World.h"
#include "ShadeRec.h"

SingleSphere::SingleSphere()
	: Tracer()
{

}

SingleSphere::SingleSphere(World* world)
	: Tracer(world)
{

}

SingleSphere::~SingleSphere()
{

}
/*
RGBColor SingleSphere::TraceRay(const Ray& ray) const
{
	
	ShadeRec sr(*mWorld);
	double t;
	if (mWorld->mSphere.hit(ray, t, sr))
	{
		return (red);
	}
	else
	{
		return (black);
	}
	
}*/