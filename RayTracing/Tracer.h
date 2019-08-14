#pragma once
#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"
#include "World.h"
#include <memory>

class Tracer
{
public:
	Tracer();
	Tracer(std::shared_ptr<World> world);
	virtual ~Tracer();

	virtual RGBColor TraceRay(const Ray& ray) const;
	virtual RGBColor TraceRay(const Ray ray, const int depth) const;
protected:
	std::shared_ptr<World> mWorld;
};