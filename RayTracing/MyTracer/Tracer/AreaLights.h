#pragma once
#include "Tracer.h"

class AreaLights : public Tracer
{
public:
	AreaLights();
	AreaLights(World* world);
	~AreaLights();
	RGBColor TraceRay(const Ray ray, const int depth) const override;
};