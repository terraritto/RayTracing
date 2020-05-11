#pragma once
#include "Image.h"
#include "Texture.h"
#include "../Mapping/Mapping.h"

class ImageTexture : public Texture
{
public:
	ImageTexture();
	~ImageTexture();

	void SetImage(std::shared_ptr<Image> image);
	void SetMapping(std::shared_ptr<Mapping> map);
	RGBColor GetColor(const ShadeRec& sr) const override;
private:
	std::shared_ptr<Image> mImage;
	std::shared_ptr<Mapping> mMapping;
};