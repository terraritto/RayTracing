#pragma once
#include "Tracer.h"

class RayCast : public Tracer
{
public:
	RayCast();
	RayCast(World* world);
	~RayCast();
	RGBColor TraceRay(const Ray ray ,const int depth) const override;
};