#include "Orthographic.h"
#include "..//Utility//RGBColor.h"
#include <random>

Orthographic::Orthographic()
	: Camera()
	, mZw(100.0)
{

}

Orthographic::Orthographic(const Orthographic& og)
	: Camera(og)
	, mZw(og.mZw)
{

}

Orthographic::~Orthographic()
{

}

std::shared_ptr<Camera> Orthographic::Clone() const
{
	return std::move(std::make_shared<Camera>(*this));
}

Orthographic& Orthographic::operator=(const Orthographic& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Camera::operator=(rhs);

	mZw = rhs.mZw;

	return *this;
}

void Orthographic::SetZWindow(const double zw)
{
	mZw = zw;
}

void Orthographic::RenderScene(World& w)
{
	RGBColor pixelColor;
	ViewPlane vp(w.mViewPlane);
	Ray ray;
	Point2D pp; //sample point in [0,1] x [0,1]
	Point2D sp; //sample point on a pixel

	w.OpenWindow(vp.mHRes, vp.mVRes);
	ray.mDirection = Vector3D(0, 0, -1);

	//random
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, 1.0f);

	for (int r = 0; r < vp.mVRes; r++) //up
	{
		for (int c = 0; c <= vp.mHRes; c++) //across
		{
			pixelColor = black;

			for (int j = 0; j < vp.mNumSamples; j++)
			{
				sp = vp.mSamplerPtr->SampleUnitSquare();
				pp.mPosX = vp.mPixelSize * (c - 0.5 * vp.mHRes + sp.mPosX);
				pp.mPosY = vp.mPixelSize * (r - 0.5 * vp.mVRes + sp.mPosY);
				ray.mOrigin = Point3D(pp.mPosX, pp.mPosY, mZw);
				pixelColor += w.mTracerPtr->TraceRay(ray);
			}

			pixelColor /= vp.mNumSamples;
			w.DisplayPixel(r, c, pixelColor);
		}
	}
}
