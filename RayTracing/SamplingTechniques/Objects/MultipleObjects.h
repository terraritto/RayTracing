#pragma once
#include "../Tracer/Tracer.h"

class MultipleObjects :public Tracer
{
public:
	MultipleObjects();
	MultipleObjects(World* worldPtr);
	~MultipleObjects();

	RGBColor TraceRay(const Ray& ray) const override;
};