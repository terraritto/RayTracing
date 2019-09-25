#include "StereoCamera.h"

StereoCamera::StereoCamera()
	: Camera()
	, mViewing(EViewingType::EParallel)
	, mPixelGap(5)
	, mBeta(10.0f)
	, mLeftCameraPtr(nullptr)
	, mRightCameraPtr(nullptr)

{

}

StereoCamera::StereoCamera(const StereoCamera& stereo)
	: Camera(stereo)
	, mViewing(stereo.mViewing)
	, mPixelGap(stereo.mPixelGap)
	, mBeta(stereo.mBeta)
	, mLeftCameraPtr(stereo.mLeftCameraPtr)
	, mRightCameraPtr(stereo.mRightCameraPtr)
{

}

StereoCamera::~StereoCamera()
{

}

std::shared_ptr<Camera> StereoCamera::Clone() const
{
	return std::move(std::make_shared<StereoCamera>(*this));
}

StereoCamera& StereoCamera::operator=(const StereoCamera& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Camera::operator=(rhs);

	mViewing = rhs.mViewing;
	mPixelGap = rhs.mPixelGap;
	mBeta = rhs.mBeta;
	mRightCameraPtr = rhs.mRightCameraPtr;
	mLeftCameraPtr = rhs.mLeftCameraPtr;

	return *this;
}

void StereoCamera::SetupCameras()
{
	double r = mEye.Length(mLookAt);
	double x = r * std::tan(0.5 * mBeta * PI_ON_180);

	mLeftCameraPtr->SetEye(mEye - x * mU);
	mLeftCameraPtr->SetLookAt(mLookAt - x * mU);
	mLeftCameraPtr->ComputeUVW();

	mRightCameraPtr->SetEye(mEye + x * mU);
	mRightCameraPtr->SetLookAt(mLookAt + x * mU);
	mRightCameraPtr->ComputeUVW();
}

void StereoCamera::RenderScene(const World& w)
{
	ViewPlane vp = w.mViewPlane;
	int hRes = vp.mHRes;
	int vRes = vp.mVRes;

	w.OpenWindow(2 * hRes + mPixelGap, vRes);

	double r = mEye.Length(mLookAt);
	double x = r * std::tan(0.5 * mBeta * PI_ON_180);

	if (mViewing == EViewingType::EParallel)
	{

	}

	if (mViewing == EViewingType::ETransverse)
	{

	}
}
