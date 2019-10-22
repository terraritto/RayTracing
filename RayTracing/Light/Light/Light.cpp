#include "Light.h"
#include "../Maths/Constants.h"

Light::Light()
{

}

Light::Light(const Light& ls)
{

}

Light::~Light()
{

}

Light& Light::operator=(const Light& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	return *this;
}

RGBColor Light::L(ShadeRec& sr)
{
	return black;
}
