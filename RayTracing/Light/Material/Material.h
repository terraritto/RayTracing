#pragma once
#include "../Utility/RGBColor.h"
#include "../Utility/ShadeRec.h"

class ShadeRec;

class Material
{
public:
	Material();
	Material(const Material& material);
	virtual ~Material();

	std::shared_ptr<Material> Clone() const { return std::make_shared<Material>(*this); };
	virtual RGBColor Shade(ShadeRec& sr);
	virtual RGBColor AreaLightShade(ShadeRec& sr);
	virtual RGBColor PathShade(ShadeRec& sr);
protected:
	Material& operator=(const Material& rhs);
};