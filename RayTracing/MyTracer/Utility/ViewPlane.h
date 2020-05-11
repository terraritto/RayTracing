#pragma once
#include "../Sampler/Sampler.h"
#include <memory>

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
	void SetSamples(const int n);
	void SetSampler(std::shared_ptr<Sampler> sp);
	void SetGamma(const float g);
	void SetIsShowOutOfGamut(const bool is);
	void SetMaxDepth(const int depth);

	int mHRes; //Horizontal Image Resolution
	int mVRes; //Vertical Image Resolution
	float mPixelSize; //Pixel Size
	int mNumSamples; // number of samples per pixel
	float mGamma; //monitor gamma factor
	float mInvGamma; //one over gamma
	int mMaxDepth; // max depth for reflective object
	bool mIsShowOutOfGamut;
	std::shared_ptr<Sampler> mSamplerPtr;
};