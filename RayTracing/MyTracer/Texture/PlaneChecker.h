#pragma once
#include "Texture.h"

class PlaneChecker : public Texture
{
public:
	PlaneChecker();
	~PlaneChecker();

	void SetColor1(const RGBColor& color);
	void SetColor2(const RGBColor& color);
	void SetOutlineColor(const RGBColor& color);
	void SetSize(const float s);
	void SetOutlineWidth(const float ow);

	RGBColor GetColor(const ShadeRec& sr) const override;
private:
	RGBColor mColor1;
	RGBColor mColor2;
	RGBColor mOutlineColor;
	float mSize;
	float mOutlineWidth;
};