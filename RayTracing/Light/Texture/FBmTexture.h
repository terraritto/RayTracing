#pragma once
#include "Image.h"
#include "Texture.h"
#include "../Noise/LatticeNoise.h"

class FBmTexture : public Texture
{
public:
	FBmTexture();
	~FBmTexture();

	RGBColor GetColor(const ShadeRec& sr) const override;

	void SetNoise(std::shared_ptr<LatticeNoise> noise);
	void SetColor(const RGBColor& col);
	void SetMinValue(float value);
	void SetMaxValue(float value);
private:
	std::shared_ptr<LatticeNoise> mNoisePtr;
	RGBColor mColor;
	float mMinValue;
	float mMaxValue;
};