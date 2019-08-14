#include "ViewPlane.h"

ViewPlane::ViewPlane()
	: mHRes(400)
	, mVRes(400)
	, mPixelSize(1.0)
	, mGamma(1.0)
	, mInvGamma(1.0)
{

}

ViewPlane::ViewPlane(const ViewPlane& vp)
	: mHRes(vp.mHRes)
	, mVRes(vp.mVRes)
	, mPixelSize(vp.mPixelSize)
	, mGamma(vp.mGamma)
	, mInvGamma(vp.mInvGamma)
{

}

ViewPlane& ViewPlane::operator=(const ViewPlane& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	
	mHRes = rhs.mHRes;
	mVRes = rhs.mVRes;
	mPixelSize = rhs.mPixelSize;
	mGamma = rhs.mGamma;
	mInvGamma = rhs.mInvGamma;

	return *this;
}

ViewPlane::~ViewPlane() 
{

}

//setter
void ViewPlane::SetHRes(const int hRes)
{
	mHRes = hRes;
}

void ViewPlane::SetVRes(const int vRes)
{
	mVRes = vRes;
}

void ViewPlane::SetPixelSize(const float size)
{
	mPixelSize = size;
}

void ViewPlane::SetGamma(const float gamma)
{
	mGamma = gamma;
	mInvGamma = 1.0 / gamma;
}