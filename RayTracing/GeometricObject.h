#pragma once
#include "RGBColor.h"
#include <memory>

class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);
	virtual ~GeometricObject();

	virtual bool hit(const class Ray& ray, double& t, class ShadeRec& s) const = 0;

protected:
	RGBColor mColor;
};