#pragma once

class ViewPlane
{
public:
	ViewPlane();
	ViewPlane(const ViewPlane& vp);
	ViewPlane& operator=(const ViewPlane& rhs);
	~ViewPlane();

	void SetHRes(const int hRes);
	void SetVRes(const int vRes);
	void SetPixelSize(const float size);
	void SetGamma(const float g);

	int mHRes; //Horizontal Image Resolution
	int mVRes; //Vertical Image Resolution
	int mPixelSize; //Pixel Size
	float mGamma; //monitor gamma factor
	float mInvGamma; //one over gamma
};