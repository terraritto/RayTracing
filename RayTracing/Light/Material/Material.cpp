#include "Material.h"
#include "../Maths/Constants.h"

Material::Material()
{

}

Material::Material(const Material& material)
{

}

Material::~Material()
{
	
}

RGBColor Material::Shade(ShadeRec& sr)
{
	return black;
}


RGBColor Material::AreaLightShade(ShadeRec& sr)
{
	return black;
}

RGBColor Material::PathShade(ShadeRec& sr)
{
	return black;
}

RGBColor Material::GetLe(ShadeRec& sr) const
{
	return black;
}

Material& Material::operator=(const Material& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	return *this;
}
