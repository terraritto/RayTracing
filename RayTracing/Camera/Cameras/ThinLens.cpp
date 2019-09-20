#include "ThinLens.h"

ThinLens::ThinLens()
	: Camera()
	, mLensRadius(1.0f)
	, mDistance(50.0f)
	, mFocalLength(75.0f)
	, mZoom(1.0f)
{

}

ThinLens::ThinLens(const ThinLens& tl)
	: Camera(tl)
	, mLensRadius(tl.mLensRadius)
	, mDistance(tl.mDistance)
	, mFocalLength(tl.mFocalLength)
	, mZoom(tl.mZoom)
{

}

ThinLens::~ThinLens()
{

}

std::shared_ptr<Camera> ThinLens::Clone() const
{
	return std::move(std::make_shared<ThinLens>(*this));
}

ThinLens& ThinLens::operator=(const ThinLens& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Camera::operator=(rhs);
	
	mLensRadius = rhs.mLensRadius;
	mDistance = rhs.mDistance;
	mFocalLength = rhs.mFocalLength;
	mZoom = rhs.mZoom;
	mSamplerPtr = rhs.mSamplerPtr;

	return *this;
}

Vector3D ThinLens::GetDirection(const Point2D& pixelPoint, Point2D& lensPoint) const
{
	Point2D p; // hit point on focal plane
	p.mPosX = pixelPoint.mPosX * mFocalLength / mDistance;
	p.mPosY = pixelPoint.mPosY * mFocalLength / mDistance;

	Vector3D dir = (p.mPosX - lensPoint.mPosX) * mU + (p.mPosY - lensPoint.mPosY) * mV - mFocalLength * mW;
	dir.Normalize();

	return dir;
}

void ThinLens::RenderScene(const World& w)
{
	RGBColor L;
	ViewPlane vp(w.mViewPlane);
	Ray ray;
	int depth = 0;
	
	Point2D sp; // sample point in [0,1] x [0,1]
	Point2D pp; // sample point on a pixel
	Point2D dp; // sample point on unit disk
	Point2D lp; // sample point on lens

	w.OpenWindow(vp.mHRes, vp.mVRes);
	vp.mPixelSize /= mZoom;

	for (int r = 0; r < vp.mVRes - 1; r++)
	{
		for (int c = 0; c < vp.mHRes - 1; c++)
		{
			L = black;

			for (int n = 0; n < vp.mNumSamples; n++)
			{
				sp = vp.mSamplerPtr->SampleUnitSquare();
				pp.mPosX = vp.mPixelSize * (c - vp.mHRes / 2.0 + sp.mPosX);
				pp.mPosY = vp.mPixelSize * (r - vp.mVRes / 2.0 + sp.mPosY);

				dp = mSamplerPtr->SampleUnitDisk();
				lp = dp * mLensRadius;

				ray.mOrigin = mEye + lp.mPosX * mU + lp.mPosY * mV;
				ray.mDirection = GetDirection(pp, lp);
				L += w.mTracerPtr->TraceRay(ray,depth);
			}

			L /= vp.mNumSamples;
			L *= mExposureTime;
			w.DisplayPixel(r, c, L);
		}
	}
}

void ThinLens::SetSampler(std::shared_ptr<Sampler> sp)
{
	if (mSamplerPtr)
	{
		mSamplerPtr.reset();
		mSamplerPtr = nullptr;
	}

	mSamplerPtr = sp;
	mSamplerPtr->MapSamplesToUnitDisk();
}

void ThinLens::SetViewDistance(float distance)
{
	mDistance = distance;
}

void ThinLens::SetFocalLength(float length)
{
	mFocalLength = length;
}

void ThinLens::SetLensRadius(float rad)
{
	mLensRadius = rad;
}
