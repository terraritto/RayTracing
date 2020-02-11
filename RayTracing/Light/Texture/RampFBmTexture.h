#pragma once
#include "Image.h"
#include "Texture.h"
#include "../Noise/LatticeNoise.h"

class RampFBmTexture : public Texture
{
public:
	RampFBmTexture();
	~RampFBmTexture();

	RGBColor GetColor(const ShadeRec& sr) const override;

	void SetNoise(std::shared_ptr<LatticeNoise> noise);
	void SetImage(std::shared_ptr<Image> image);
	void SetAmount(float amount);
private:
	std::shared_ptr<Image> mRampPtr;
	std::shared_ptr<LatticeNoise> mNoisePtr;
	float mAmount;
};