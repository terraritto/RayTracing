#pragma once
#include "../Maths/Vector3D.h"
#include "../Utility/RGBColor.h"
#include "../Maths/Ray.h"
#include "../Utility/ShadeRec.h"
#include <memory>

class ShadeRec;

class Light
{
public:
	Light();
	Light(const Light& ls);
	~Light();

	Light& operator=(const Light& rhs);

	virtual Vector3D GetDirection(ShadeRec& sr) = 0;
	virtual RGBColor L(ShadeRec& sr);
};