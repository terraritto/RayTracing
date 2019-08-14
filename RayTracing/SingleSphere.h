#pragma once
#include "Tracer.h"

class SingleSphere : public Tracer
{
public:
	SingleSphere();
	SingleSphere(std::shared_ptr<World> world);

	virtual ~SingleSphere();
	RGBColor TraceRay(const Ray& ray) const override;
};