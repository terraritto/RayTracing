#include <cmath>
#include "RGBColor.h"

RGBColor::RGBColor()
	: mRed(0.0)
	, mGreen(0.0)
	, mBlue(0.0)
{

}

RGBColor::RGBColor(float c)
	: mRed(c)
	, mGreen(c)
	, mBlue(c)
{

}

RGBColor::RGBColor(float r, float g, float b)
	: mRed(r)
	, mGreen(g)
	, mBlue(b)
{

}

RGBColor::RGBColor(const RGBColor& c)
	: mRed(c.mRed)
	, mGreen(c.mGreen)
	, mBlue(c.mBlue)
{

}

RGBColor::~RGBColor()
{

}

RGBColor& RGBColor::operator=(const RGBColor& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mRed = rhs.mRed;
	mGreen = rhs.mGreen;
	mBlue = rhs.mBlue;

	return *this;
}

RGBColor RGBColor::operator+(const RGBColor& c) const
{
	return (RGBColor(mRed + c.mRed, mGreen + c.mGreen, mBlue + c.mBlue));
}

RGBColor& RGBColor::operator+=(const RGBColor& c)
{
	mRed += c.mRed;
	mGreen += c.mGreen;
	mBlue += c.mBlue;
	return *this;
}

RGBColor RGBColor::operator*(const float a) const
{
	return (RGBColor(mRed * a, mGreen * a, mBlue * a));
}

RGBColor& RGBColor::operator*=(const float a)
{
	mRed *= a;
	mGreen *= a;
	mBlue *= a;
	return *this;
}

RGBColor RGBColor::operator/(const float a) const
{
	return (RGBColor(mRed / a, mGreen / a, mBlue / a));
}

RGBColor& RGBColor::operator/=(const float a)
{
	mRed /= a;
	mGreen /= a;
	mBlue /= a;
	return *this;
}

RGBColor RGBColor::operator*(const RGBColor& c) const
{
	return (RGBColor(mRed * c.mRed, mGreen * c.mGreen, mBlue * c.mBlue));
}

bool RGBColor::operator==(const RGBColor& c) const
{
	return (mRed == c.mRed && mGreen == c.mGreen && mBlue == c.mBlue);
}

RGBColor operator*(const float a, const RGBColor& c)
{
	return (RGBColor(a * c.mRed, a * c.mGreen, a * c.mBlue));
}

RGBColor RGBColor::PowColor(float p) const
{
	return (RGBColor(std::powf(mRed, p), std::powf(mGreen, p), std::powf(mBlue, p)));
}

float RGBColor::Average() const
{
	return (0.333333333333 * (mRed + mGreen + mBlue));
}