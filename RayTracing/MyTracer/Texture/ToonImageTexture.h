#pragma once
#include "AlphaImage.h"
#include "Texture.h"
#include "../Mapping/Mapping.h"

class ToonImageTexture : public Texture
{
public:
	ToonImageTexture();
	~ToonImageTexture();

	void SetImage(std::shared_ptr<AlphaImage> image);
	void SetMapping(std::shared_ptr<Mapping> map);
	RGBColor GetToon(const float f) const override;

private:
	std::shared_ptr<AlphaImage> mImage;
	std::shared_ptr<Mapping> mMapping;
};