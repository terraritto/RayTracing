#pragma once
#include "RGBColor.h"

class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);
	virtual ~GeometricObject();

	virtual GeometricObject* clone() const = 0;

	virtual bool hit(const class Ray& ray, double& t, class ShadeRec& s) const = 0;

protected:
	RGBColor mColor;
};