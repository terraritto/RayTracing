#pragma once
#include <array>
#include <vector>
#include "../Utility/RGBColor.h"

class Image
{
public:
	Image() = default;
	~Image() = default;
	Image(const Image& im) = default;

	void ReadPpmFile(std::string fileName);
	RGBColor GetColor(int row, int column);

public:
	int mHres;
	int mVres;

private:
	std::vector<std::vector<RGBColor>> mPixel;
};