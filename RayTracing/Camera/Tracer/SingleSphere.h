#pragma once
#include "Tracer.h"

class SingleSphere : public Tracer
{
public:
	SingleSphere();
	SingleSphere(World* world);

	virtual ~SingleSphere();
	//RGBColor TraceRay(const Ray& ray) const override;
};