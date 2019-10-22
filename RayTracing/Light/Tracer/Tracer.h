#pragma once
#include "../Maths/Constants.h"
#include "../Maths/Ray.h"
#include "../Utility/RGBColor.h"
#include "../Utility/World.h"
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
	virtual RGBColor TraceRay(const Ray ray, float& tMin, const int depth) const;
protected:
	World* mWorld;
};