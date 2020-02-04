#include "FlatUVMeshTriangle.h"

FlatUVMeshTriangle::FlatUVMeshTriangle(std::shared_ptr<Mesh> mesh_ptr, const int i0, const int i1, const int i2)
	: FlatMeshTriangle(mesh_ptr, i0, i1, i2)
{
}

FlatUVMeshTriangle::FlatUVMeshTriangle(const FlatUVMeshTriangle& fmt)
	: FlatMeshTriangle(fmt)
{
}

FlatUVMeshTriangle& FlatUVMeshTriangle::operator=(const FlatUVMeshTriangle& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	FlatMeshTriangle::operator=(rhs);

	return *this;
}

std::shared_ptr<FlatUVMeshTriangle> FlatUVMeshTriangle::Clone() const
{
	return std::make_shared<FlatUVMeshTriangle>(*this);
}

bool FlatUVMeshTriangle::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	Point3D mV0 = mMeshPtr->mVertices[mIndex0];
	Point3D mV1 = mMeshPtr->mVertices[mIndex1];
	Point3D mV2 = mMeshPtr->mVertices[mIndex2];

	double a = mV0.mPosX - mV1.mPosX, b = mV0.mPosX - mV2.mPosX;
	double c = ray.mDirection.mPosX, d = mV0.mPosX - ray.mOrigin.mPosX;
	double e = mV0.mPosY - mV1.mPosY, f = mV0.mPosY - mV2.mPosY;
	double g = ray.mDirection.mPosY, h = mV0.mPosY - ray.mOrigin.mPosY;
	double i = mV0.mPosZ - mV1.mPosZ, j = mV0.mPosZ - mV2.mPosZ;
	double k = ray.mDirection.mPosZ, l = mV0.mPosZ - ray.mOrigin.mPosZ;

	double m = f * k - g * j, n = h * k - g * l;
	double p = f * l - h * j, q = g * i - e * k;
	double s = e * j - f * i;

	double invDenom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;

	// first check
	if (beta < 0.0)
	{
		return false;
	}

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * invDenom;

	// second check
	if (gamma < 0.0)
	{
		return false;
	}

	// third check
	if (beta + gamma > 1.0)
	{
		return false;
	}

	double e3 = a * p - b * r + d * s;
	double t = e3 * invDenom;

	// final check
	if (t < kEpsilon)
	{
		return false;
	}

	//hit
	tMin = t;
	sr.mNormal = mNormal;
	sr.mU = InterpolateU(beta, gamma);
	sr.mV = InterpolateV(beta, gamma);
	sr.mLocalHitPoint = ray.mOrigin + t * ray.mDirection;

	return true;
}
