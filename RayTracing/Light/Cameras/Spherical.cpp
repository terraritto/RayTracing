#include "Spherical.h"
#include "..//Maths/Constants.h"
#include <cmath>

Spherical::Spherical()
	: Camera()
	, mPsiMax(45)
	, mLambdaMax(90)
{

}

Spherical::Spherical(const Spherical& sphere)
	: Camera(sphere)
	, mPsiMax(sphere.mPsiMax)
	, mLambdaMax(sphere.mLambdaMax)
{

}

Spherical::~Spherical()
{

}

std::shared_ptr<Camera> Spherical::Clone() const
{
	return std::move(std::make_shared<Spherical>(*this));
}

Spherical& Spherical::operator=(const Spherical& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Camera::operator=(rhs);
	
	mPsiMax = rhs.mPsiMax;
	mLambdaMax = rhs.mLambdaMax;

	return *this;
}

Vector3D Spherical::GetDirection(const Point2D& pp, const int hRes, const int vRes, const float s) const
{
	Point2D pn(2.0 / (s * hRes) * pp.mPosX, 2.0 / (s * vRes) * pp.mPosY);

	// compute angle
	float lambda = pn.mPosX * mLambdaMax * PI_ON_180;
	float psi = pn.mPosY * mPsiMax * PI_ON_180;

	// compute phi and theta
	float phi = PI - lambda;
	float theta = PI / 2 - psi;

	float sinPhi = std::sin(phi);
	float cosPhi = std::cos(phi);
	float sinTheta = std::sin(theta);
	float cosTheta = std::cos(theta);

	Vector3D dir = sinTheta * sinPhi * mU + cosTheta * mV + sinTheta * cosPhi * mW;

	return dir;
}

void Spherical::RenderScene(const World& w)
{
	RGBColor L;
	ViewPlane vp(w.mViewPlane);
	int hRes = vp.mHRes;
	int vRes = vp.mVRes;
	float s = vp.mPixelSize;
	Ray ray;
	int depth = 0;
	Point2D sp; // sample point in [0,1] x [0,1]
	Point2D pp; // sample point on the pixel

	w.OpenWindow(vp.mHRes, vp.mVRes);
	ray.mOrigin = mEye;

	for (int r = 0; r < vRes; r++)
	{
		for (int c = 0; c < hRes; c++)
		{
			L = black;

			for (int j = 0; j < vp.mNumSamples; j++)
			{
				sp = vp.mSamplerPtr->SampleUnitSquare();
				pp.mPosX = s * (c - 0.5 * hRes + sp.mPosX);
				pp.mPosY = s * (r - 0.5 * vRes + sp.mPosY);
				ray.mDirection = GetDirection(pp, hRes, vRes, s);
				L += w.mTracerPtr->TraceRay(ray);
			
			}

			L /= vp.mNumSamples;
			L *= mExposureTime;
			w.DisplayPixel(r, c, L);
		}
	}
}
