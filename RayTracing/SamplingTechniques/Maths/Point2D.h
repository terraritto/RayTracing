#pragma once
class Point2D
{
public:
	float mPosX, mPosY;

	Point2D();
	Point2D(const float arg);
	Point2D(const float x, const float y);
	Point2D(const Point2D& p);
	~Point2D();
	
	Point2D& operator=(const Point2D& rhs);
	Point2D operator*(const float a);
};