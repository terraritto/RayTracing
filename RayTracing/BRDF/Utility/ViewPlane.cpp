#include "ViewPlane.h"
#include "../Sampler/MultiJittered.h"
#include "../Sampler/Regular.h"

ViewPlane::ViewPlane()
	: mHRes(400)
	, mVRes(400)
	, mPixelSize(1.0)
	, mNumSamples(1)
	, mGamma(1.0)
	, mInvGamma(1.0)
	, mSamplerPtr(nullptr)
{

}

ViewPlane::ViewPlane(const ViewPlane& vp)
	: mHRes(vp.mHRes)
	, mVRes(vp.mVRes)
	, mPixelSize(vp.mPixelSize)
	, mNumSamples(vp.mNumSamples)
	, mGamma(vp.mGamma)
	, mInvGamma(vp.mInvGamma)
	, mSamplerPtr(vp.mSamplerPtr)
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
	mNumSamples = rhs.mNumSamples;
	mGamma = rhs.mGamma;
	mInvGamma = rhs.mInvGamma;
	mSamplerPtr = rhs.mSamplerPtr;

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

void ViewPlane::SetSamples(const int n)
{
	mNumSamples = n;

	if (mSamplerPtr)
	{
		mSamplerPtr.reset();
		mSamplerPtr = nullptr;
	}

	if (mNumSamples > 1)
	{
		mSamplerPtr = std::move(std::make_shared<MultiJittered>(mNumSamples));
	}
	else
	{
		mSamplerPtr = std::move(std::make_shared<Regular>(mNumSamples));
	}
}

void ViewPlane::SetSampler(std::shared_ptr<Sampler> sp)
{
	if (mSamplerPtr)
	{
		mSamplerPtr.reset();
	}

	mNumSamples = sp->GetNumSamples();
	mSamplerPtr = sp;
}

void ViewPlane::SetGamma(const float gamma)
{
	mGamma = gamma;
	mInvGamma = 1.0 / gamma;
}