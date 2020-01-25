#pragma once
#include "../Utility/RGBColor.h"
#include "../Utility/ShadeRec.h"

class Texture
{
public:
	Texture() = default;
	Texture(const Texture& tex) = default;
	~Texture() = default;

	virtual RGBColor GetColor(const ShadeRec& sr) const = 0;
};