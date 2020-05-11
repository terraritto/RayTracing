#pragma once
#include "Tracer.h"

class PathTrace : public Tracer
{
public:
	PathTrace(World* world);
	~PathTrace();
	RGBColor TraceRay(const Ray ray, const int depth) const override;
private:
	PathTrace(); // can't use
};