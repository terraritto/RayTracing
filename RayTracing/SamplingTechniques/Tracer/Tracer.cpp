#include "Tracer.h"

Tracer::Tracer()
	: mWorld(nullptr)
{

}

Tracer::Tracer(World* world)
	: mWorld(world)
{

}

Tracer::~Tracer()
{
}

RGBColor Tracer::TraceRay(const Ray& ray) const
{
	return black;
}

RGBColor Tracer::TraceRay(const Ray ray, const int depth) const
{
	return (black);
}