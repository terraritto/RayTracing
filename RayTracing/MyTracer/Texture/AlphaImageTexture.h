#pragma once
#pragma once
#include "AlphaImage.h"
#include "Texture.h"
#include "../Mapping/Mapping.h"

class AlphaImageTexture : public Texture
{
public:
	AlphaImageTexture();
	~AlphaImageTexture();

	void SetImage(std::shared_ptr<AlphaImage> image);
	void SetMapping(std::shared_ptr<Mapping> map);
	RGBColor GetColor(const ShadeRec& sr) const override;
	float GetAlpha(const ShadeRec& sr) const override;
private:
	std::shared_ptr<AlphaImage> mImage;
	std::shared_ptr<Mapping> mMapping;
};