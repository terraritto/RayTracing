#pragma once

class RGBColor
{
public:
	float mRed, mGreen, mBlue;

	RGBColor();
	RGBColor(float c);
	RGBColor(float r, float g, float b);
	RGBColor(const RGBColor& c);
	~RGBColor();

	RGBColor& operator=(const RGBColor& rhs);
	RGBColor operator+(const RGBColor& c) const;
	RGBColor& operator+=(const RGBColor& c);
	RGBColor operator*(const float a) const;
	RGBColor& operator*=(const float a);
	RGBColor operator/(const float a) const;
	RGBColor& operator/=(const float a);
	RGBColor operator*(const RGBColor& c) const;
	bool operator==(const RGBColor& c) const;
	RGBColor PowColor(float p) const;
	float Average() const; // the average of the three components
};

RGBColor operator*(const float a, const RGBColor& c);