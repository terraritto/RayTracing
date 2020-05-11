#pragma once
#include "Tracer.h"

class Whitted : public Tracer
{
public:
	Whitted(World* world);
	~Whitted();
	RGBColor TraceRay(const Ray ray, const int depth) const override;
	RGBColor TraceRay(const Ray ray, float& tMin, const int depth) const override;

private:
	Whitted(); // can't use
};