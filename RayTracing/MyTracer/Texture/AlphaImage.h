#pragma once
#include <array>
#include <vector>
#include "../Utility/RGBColor.h"

class AlphaImage
{
public:
	AlphaImage() = default;
	~AlphaImage() = default;
	AlphaImage(const AlphaImage& im) = default;

	void ReadPpmFile(std::string fileName);
	RGBColor GetColor(int row, int column);

public:
	int mHres;
	int mVres;
private:
	std::vector<std::vector<RGBColor>> mPixel;
	std::vector<std::vector<float>> mAlpha;
};