#pragma once
#include "Image.h"
#include "Texture.h"
#include "../Noise/LatticeNoise.h"

class WrappedTexture : public Texture
{
public:
	WrappedTexture();
	~WrappedTexture();

	RGBColor GetColor(const ShadeRec& sr) const override;

	void SetNoise(std::shared_ptr<LatticeNoise> noise);
	void SetColor(const RGBColor& col);
	void SetExpansionNumber(const float num);
private:
	std::shared_ptr<LatticeNoise> mNoisePtr;
	RGBColor mColor;
	float mExpansionNumber;
};