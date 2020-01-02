#include "MeshTriangle.h"

MeshTriangle::MeshTriangle()
	: GeometricObject()
	, mMeshPtr(nullptr)
	, mIndex0(0), mIndex1(0), mIndex2(0)
	, mNormal()
	, mArea(0.0f)
{
}

MeshTriangle::MeshTriangle(std::shared_ptr<Mesh> mesh_ptr, const int i1, const int i2, const int i3)
	: GeometricObject()
	, mMeshPtr(mesh_ptr)
	, mIndex0(i1) , mIndex1(i2), mIndex2(i3)
	, mNormal()
	, mArea(0.0f)
{
}

MeshTriangle::MeshTriangle(const MeshTriangle& mt)
	: GeometricObject(mt)
	, mMeshPtr(mt.mMeshPtr) // just the pointer
	, mIndex0(mt.mIndex0)
	, mIndex1(mt.mIndex1)
	, mIndex2(mt.mIndex2)
	, mNormal(mt.mNormal)
	, mArea(mt.mArea)
{
}

MeshTriangle::~MeshTriangle()
{
}

MeshTriangle& MeshTriangle::operator=(const MeshTriangle& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	GeometricObject::operator=(rhs);

	mMeshPtr = rhs.mMeshPtr; // just the pointer
	mIndex0 = rhs.mIndex0;
	mIndex1 = rhs.mIndex1;
	mIndex2 = rhs.mIndex2;
	mNormal = rhs.mNormal;
	mArea = rhs.mArea;

	return *this;
}

std::shared_ptr<MeshTriangle> MeshTriangle::Clone() const
{
	return std::make_shared<MeshTriangle>(*this);
}

bool MeshTriangle::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	return false;
}

bool MeshTriangle::Shadow_hit(const Ray& ray, float& tmin) const
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
	tmin = t;

	return true;
}

void MeshTriangle::ComputeNormal(const bool reverse_normal)
{
	mNormal = (mMeshPtr->mVertices[mIndex1] - mMeshPtr->mVertices[mIndex0]) ^
		(mMeshPtr->mVertices[mIndex2] - mMeshPtr->mVertices[mIndex0]);
	mNormal.Normalize();

	if (reverse_normal)
	{
		mNormal = -mNormal;
	}
}

Normal MeshTriangle::GetNormal(const Point3D& p)
{
	return mNormal;
}

BBox MeshTriangle::GetBoundingBox() const
{
	double delta = 0.00001;
	Point3D ansMin, ansMax;

	Point3D mV0 = mMeshPtr->mVertices[mIndex0];
	Point3D mV1 = mMeshPtr->mVertices[mIndex1];
	Point3D mV2 = mMeshPtr->mVertices[mIndex2];

	//p0
	ansMin.mPosX = std::min({ mV0.mPosX,mV1.mPosX,mV2.mPosX });
	ansMin.mPosY = std::min({ mV0.mPosY,mV1.mPosY,mV2.mPosY });
	ansMin.mPosZ = std::min({ mV0.mPosZ,mV1.mPosZ,mV2.mPosZ });
	//p1
	ansMax.mPosX = std::max({ mV0.mPosX,mV1.mPosX,mV2.mPosX });
	ansMax.mPosY = std::max({ mV0.mPosY,mV1.mPosY,mV2.mPosY });
	ansMax.mPosZ = std::max({ mV0.mPosZ,mV1.mPosZ,mV2.mPosZ });

	//minus or plus delta ,It means make BBox
	ansMin = ansMin - delta;
	ansMax = ansMax + delta;

	return BBox(ansMin, ansMax);
}
