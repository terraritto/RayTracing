#include "FishEye.h"
#include "..//Maths/Constants.h"
#include <cmath>

FishEye::FishEye()
	: Camera()
	, mPsiMax(180)
{

}

FishEye::FishEye(const FishEye& eye)
	: Camera(eye)
	, mPsiMax(eye.mPsiMax)
{

}

FishEye::~FishEye()
{

}

std::shared_ptr<Camera> FishEye::Clone() const
{
	return std::move(std::make_shared<FishEye>(*this));
}

FishEye& FishEye::operator=(const FishEye& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Camera::operator=(rhs);

	mPsiMax = rhs.mPsiMax;

	return *this;
}

Vector3D FishEye::GetDirection(const Point2D& p, const int hRes, const int vRes, const float s, float& r) const
{
	Point2D pn(2.0 / (s * hRes) * p.mPosX, 2.0 / (s * vRes) * p.mPosY);
	r = pn.mPosX * pn.mPosX + pn.mPosY * pn.mPosY;

	if (r <= 1.0)
	{
		float rad = std::sqrt(r);
		float psi = rad * mPsiMax * PI_ON_180 / 2;
		float sinPsi = std::sin(psi);
		float cosPsi = std::cos(psi);
		float sinAlpha = pn.mPosY / rad;
		float cosAlpha = pn.mPosX / rad;
		Vector3D dir =
			sinPsi * cosAlpha * mU
			+ sinPsi * sinAlpha * mV
			- cosPsi * mW;

		return dir;
	}
	else
	{
		return Vector3D(0.0);
	}
}

void FishEye::RenderScene(World& w)
{
	RGBColor L;
	ViewPlane vp(w.mViewPlane);
	int hRes = vp.mHRes;
	int vRes = vp.mVRes;
	float s = vp.mPixelSize;
	float radSq; //sum of squares of normalized device coordinates
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
				ray.mDirection = GetDirection(pp, hRes, vRes, s, radSq);
				if (radSq <= 1.0)
				{
					L += w.mTracerPtr->TraceRay(ray,depth);
				}
			}

			L /= vp.mNumSamples;
			L *= mExposureTime;
			w.DisplayPixel(r, c, L);
		}
	}
}
