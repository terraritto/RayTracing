#include "ConstantColor.h"

ConstantColor::ConstantColor(const RGBColor color)
	: mColor(color)
{
}

ConstantColor::ConstantColor(const ConstantColor& cc)
	: mColor(cc.mColor)
{
}

ConstantColor::~ConstantColor()
{
}

void ConstantColor::SetColor(const RGBColor& c)
{
	mColor = c;
}

void ConstantColor::SetColor(const float c)
{
	mColor = RGBColor(c);
}

void ConstantColor::SetColor(const float r, const float g, const float b)
{
	mColor = RGBColor(r, g, b);
}

RGBColor ConstantColor::GetColor(const ShadeRec& sr) const
{
	return mColor;
}
