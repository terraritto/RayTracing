#pragma once
#include "Texture.h"

class ConstantColor : public Texture
{
public:
	ConstantColor() = default;
	ConstantColor(const RGBColor color);
	ConstantColor(const ConstantColor& cc);
	~ConstantColor();

	void SetColor(const RGBColor& c);
	void SetColor(const float c);
	void SetColor(const float r, const float g, const float b);

	RGBColor GetColor(const ShadeRec& sr) const override;
private:
	RGBColor mColor;
};