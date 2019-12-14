#include "Rectangle.h"

Rectangler::Rectangler(Point3D p0, Vector3D a, Vector3D b, Normal n)
	: GeometricObject()
	, mP0(p0)
	, mA(a)
	, mB(b)
	, mNormal(n)
	, mSamplePtr(nullptr)
	, mArea(a.Length() * b.Length())
	, mInvArea(1.0/mArea)
	, mALenSquared(a.Length()*a.Length())
	, mBLenSquared(b.Length()*b.Length())
{
	mNormal.Normalize();
}

Rectangler::Rectangler(const Rectangler& rect)
	: GeometricObject(rect)
	, mP0(rect.mP0)
	, mA(rect.mA)
	, mB(rect.mB)
	, mNormal(rect.mNormal)
	, mArea(rect.mArea)
	, mInvArea(rect.mInvArea)
	, mALenSquared(rect.mALenSquared)
	, mBLenSquared(rect.mBLenSquared)
{
	if (rect.mSamplePtr)
	{
		mSamplePtr = rect.mSamplePtr->Clone();
	}
	else
	{
		mSamplePtr = nullptr;
	}
}

Rectangler& Rectangler::operator=(const Rectangler& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	GeometricObject::operator=(rhs);
	mP0 = rhs.mP0;
	mA = rhs.mA;
	mB = rhs.mB;
	mNormal = rhs.mNormal;
	mArea = rhs.mArea;
	mInvArea = rhs.mInvArea;
	mALenSquared = rhs.mALenSquared;
	mBLenSquared = rhs.mBLenSquared;
	if (rhs.mSamplePtr)
	{
		mSamplePtr = rhs.mSamplePtr->Clone();
	}
	else
	{
		mSamplePtr = nullptr;
	}

	return *this;
}

std::shared_ptr<Rectangler> Rectangler::Clone() const
{
	return std::make_shared<Rectangler>(*this);
}

Rectangler::~Rectangler()
{
}

bool Rectangler::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	double t = (mP0 - ray.mOrigin) * mNormal / (ray.mDirection * mNormal);

	if (t <= kEpsilon)
	{
		return false;
	}

	Point3D p = ray.mOrigin + t * ray.mDirection;
	Vector3D d = p - mP0;
	
	double ddota = d * mA;

	if ((ddota < 0.0) || (ddota > mALenSquared))
	{
		return false;
	}

	double ddotb = d * mB;
	if((ddotb <0.0) || (ddotb > mBLenSquared))
	{
		return false;
	}

	tMin = t;
	sr.mNormal = mNormal;
	sr.mLocalHitPoint = p;
	return true;
}

bool Rectangler::Shadow_hit(const Ray& ray, float& tMin) const
{
	double t = (mP0 - ray.mOrigin) * mNormal / (ray.mDirection * mNormal);

	if (t <= kEpsilon)
	{
		return false;
	}

	Point3D p = ray.mOrigin + t * ray.mDirection;
	Vector3D d = p - mP0;

	double ddota = d * mA;

	if ((ddota < 0.0) || (ddota > mALenSquared))
	{
		return false;
	}

	double ddotb = d * mB;
	if ((ddotb <0.0) || (ddotb > mBLenSquared))
	{
		return false;
	}

	tMin = t;

	return true;
}

void Rectangler::SetP0(const Point3D p0)
{
	mP0 = p0;
}

Point3D Rectangler::GetP0() const
{
	return mP0;
}

void Rectangler::SetAB(Vector3D a, Vector3D b)
{
	mA = a;
	mB = b;
	mNormal = a ^ b;
	mNormal.Normalize();
	mArea = a.Length() * b.Length();
	mInvArea = 1.0 / mArea;
	mALenSquared = a.Length() * a.Length();
	mBLenSquared = b.Length() * b.Length();
}

void Rectangler::SetSampler(std::shared_ptr<Sampler> sampler)
{
	mSamplePtr = sampler;
}

Point3D Rectangler::Sample()
{
	Point2D samplePoint = mSamplePtr->SampleUnitSquare();
	return (mP0 + samplePoint.mPosX * mA + samplePoint.mPosY * mB);
}

float Rectangler::pdf(const ShadeRec& sr)
{
	return mInvArea;
}

Normal Rectangler::GetNormal(const Point3D& p)
{
	return mNormal;
}
