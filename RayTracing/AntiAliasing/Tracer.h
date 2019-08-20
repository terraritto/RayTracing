#pragma once
#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"
#include "World.h"
#include <memory>
class World;

class Tracer
{
public:
	Tracer();
	Tracer(World* world);
	virtual ~Tracer();

	virtual RGBColor TraceRay(const Ray& ray) const;
	virtual RGBColor TraceRay(const Ray ray, const int depth) const;
protected:
	World* mWorld;
};