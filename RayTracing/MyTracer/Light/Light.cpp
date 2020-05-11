#include "Light.h"
#include "../Maths/Constants.h"

Light::Light()
	: mIsShadow(false)
{

}

Light::Light(const Light& ls)
	: mIsShadow(ls.mIsShadow)
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

	mIsShadow = rhs.mIsShadow;

	return *this;
}

RGBColor Light::L(ShadeRec& sr)
{
	return black;
}

float Light::G(const ShadeRec& sr) const
{
	return 1.0f;
}

float Light::pdf(const ShadeRec& sr) const
{
	return 1.0f;
}

bool Light::InShadow(const Ray& ray, const ShadeRec& sr) const
{
	return false;
}
