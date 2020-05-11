#pragma once
#include "Tracer.h"

class GlobalTrace : public Tracer
{
public:
	GlobalTrace(World* world);
	~GlobalTrace();
	RGBColor TraceRay(const Ray ray, const int depth) const override;
private:
	GlobalTrace(); // can't use
};