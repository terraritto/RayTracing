#include "Point2D.h"

Point2D::Point2D()
	: mPosX(0.0)
	, mPosY(0.0)
{

}

Point2D::Point2D(const float arg)
	: mPosX(arg)
	, mPosY(arg)
{

}

Point2D::Point2D(const float x, const float y)
	: mPosX(x)
	, mPosY(y)
{

}

Point2D::Point2D(const Point2D& p)
	: mPosX(p.mPosX)
	, mPosY(p.mPosY)
{

}

Point2D::~Point2D()
{

}

Point2D& Point2D::operator=(const Point2D& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mPosX = rhs.mPosX;
	mPosY = rhs.mPosY;

	return *this;
}

Point2D Point2D::operator*(const float a)
{
	return (Point2D(a * mPosX, a * mPosY));
}