#include "Camera.h"

Camera::Camera()
	: mEye(0, 0, 500)
	, mLookAt(0)
	, mRollAngle(0)
	, mUp(0, 1, 0)
	, mU(1, 0, 0)
	, mV(0, 1, 0)
	, mW(0, 0, 1)
	, mExposureTime(1.0)
{

}

Camera::Camera(const Camera& c)
	: mEye(c.mEye)
	, mLookAt(c.mLookAt)
	, mRollAngle(c.mRollAngle)
	, mUp(c.mUp)
	, mU(c.mU)
	, mV(c.mV)
	, mW(c.mW)
	, mExposureTime(c.mExposureTime)
{

}

Camera::~Camera()
{

}

Camera& Camera::operator=(const Camera& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mEye = rhs.mEye;
	mLookAt = rhs.mLookAt;
	mRollAngle = rhs.mRollAngle;
	mUp = rhs.mUp;
	mU = rhs.mU;
	mV = rhs.mV;
	mW = rhs.mW;
	mExposureTime = rhs.mExposureTime;

	return *this;
}

void Camera::ComputeUVW()
{
	mW = mEye - mLookAt;
	mW.Normalize();
	mU = mUp ^ mW;
	mU.Normalize();
	mV = mW ^ mU;
}

//setter
void Camera::SetEye(const Point3D& p)
{
	mEye = p;
}

void Camera::SetEye(const float x, const float y, const float z)
{
	mEye.mPosX = x;
	mEye.mPosY = y;
	mEye.mPosZ = z;
}

void Camera::SetLookAt(const Point3D& p)
{
	mLookAt = p;
}

void Camera::SetLookAt(const float x, const float y, const float z)
{
	mLookAt.mPosX = x;
	mLookAt.mPosY = y;
	mLookAt.mPosZ = z;
}

void Camera::SetUpVector(const Vector3D& u)
{
	mUp = u;
}

void Camera::SetUpVector(const float x, const float y, const float z)
{
	mUp.mPosX = x;
	mUp.mPosY = y;
	mUp.mPosZ = z;
}

void Camera::SetRoll(const float r)
{
	mRollAngle = r;
}

void Camera::SetExposureTime(const float exposure)
{
	mExposureTime = exposure;
}