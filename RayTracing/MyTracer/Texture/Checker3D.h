#pragma once
#include "Texture.h"

class Checker3D : public Texture
{
public:
	Checker3D();
	~Checker3D();

	void SetColor1(const RGBColor& color);
	void SetColor2(const RGBColor& color);
	void SetSize(const float s);

	RGBColor GetColor(const ShadeRec& sr) const override;
private:
	RGBColor mColor1;
	RGBColor mColor2;
	float mSize;
};