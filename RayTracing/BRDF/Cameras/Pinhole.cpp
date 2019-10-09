#include "Pinhole.h"
#include "..//Utility//RGBColor.h"
#include "..//Maths//Ray.h"
#include "..//Utility//ViewPlane.h"


Pinhole::Pinhole()
	: Camera()
	, mDistance(500)
	, mZoom(1.0)
{

}

Pinhole::Pinhole(const Pinhole& c)
	: Camera(c)
	, mDistance(c.mDistance)
	, mZoom(c.mZoom)
{

}

Pinhole::~Pinhole()
{

}

std::shared_ptr<Camera> Pinhole::Clone() const
{
	return std::move(std::make_shared<Pinhole>(*this));
}

Pinhole& Pinhole::operator=(const Pinhole& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Camera::operator=(rhs);

	mDistance = rhs.mDistance;
	mZoom = rhs.mZoom;

	return *this;
}

void Pinhole::RenderScene(const World& w)
{
	RGBColor L;
	ViewPlane vp(w.mViewPlane);
	Ray ray;
	int depth = 0; //recursion depth
	Point2D sp;
	Point2D pp;

	w.OpenWindow(vp.mHRes, vp.mVRes);
	vp.mPixelSize /= mZoom;
	ray.mOrigin = mEye;

	for (int r = 0; r < vp.mVRes; r++)
	{
		for (int c = 0; c < vp.mHRes; c++)
		{
			L = black;

			for (int j = 0; j < vp.mNumSamples; j++)
			{
				sp = vp.mSamplerPtr->SampleUnitSquare();
				pp.mPosX = vp.mPixelSize * (c - 0.5 * vp.mHRes + sp.mPosX);
				pp.mPosY = vp.mPixelSize * (r - 0.5 * vp.mVRes + sp.mPosY);
				ray.mDirection = GetDirection(pp);
				// TraceRay output black pixel now
				// so if you run any programs, image is all black.
				// if you use TraceRay(ray);, you can output ideal images. 
				L += w.mTracerPtr->TraceRay(ray);
			}
			L /= vp.mNumSamples;
			L *= mExposureTime;
			w.DisplayPixel(r, c, L);
		}
	}
}

void Pinhole::RenderStereo(const World& w, float x, int offset)
{
	RGBColor L;
	ViewPlane vp(w.mViewPlane);
	Ray ray;
	int depth = 0; //recursion depth
	Point2D sp;
	Point2D pp;

	vp.mPixelSize /= mZoom;
	ray.mOrigin = mEye;

	for (int r = 0; r < vp.mVRes; r++)
	{
		for (int c = 0; c < vp.mHRes; c++)
		{
			L = black;

			for (int j = 0; j < vp.mNumSamples; j++)
			{
				sp = vp.mSamplerPtr->SampleUnitSquare();
				pp.mPosX = vp.mPixelSize * (c - 0.5 * vp.mHRes + sp.mPosX) + x;
				pp.mPosY = vp.mPixelSize * (r - 0.5 * vp.mVRes + sp.mPosY);
				ray.mDirection = GetDirection(pp);
				// TraceRay output black pixel now
				// so if you run any programs, image is all black.
				// if you use TraceRay(ray);, you can output ideal images. 
				L += w.mTracerPtr->TraceRay(ray);
			}
			L /= vp.mNumSamples;
			L *= mExposureTime;
			w.DisplayPixel(r, c + offset, L);
		}
	}
}

void Pinhole::SetViewDistance(float d)
{
	mDistance = d;
}

void Pinhole::SetZoom(float zoomFactor)
{
	mZoom = zoomFactor;
}

Vector3D Pinhole::GetDirection(const Point2D& p) const
{
	Vector3D dir = p.mPosX * mU + p.mPosY * mV - mDistance * mW;
	dir.Normalize();
	return dir;
}