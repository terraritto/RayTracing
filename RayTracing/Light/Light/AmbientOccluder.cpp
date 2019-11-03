#include "AmbientOccluder.h"
#include "../Maths/Point3D.h"

AmbientOccluder::AmbientOccluder()
	: Light()
	, mU(Vector3D()), mV(Vector3D()), mW(Vector3D())
	, mSamplerPtr(nullptr)
{
}

AmbientOccluder::AmbientOccluder(const AmbientOccluder& ambient)
	: Light(ambient)
	, mU(ambient.mU) , mV(ambient.mV), mW(ambient.mW)
	, mColor(ambient.mColor)
	, mLs(ambient.mLs)
	, mMinAmount(ambient.mMinAmount)
{
	if (mSamplerPtr)
	{
		mSamplerPtr.reset();
	}

	if (ambient.mSamplerPtr)
	{
		mSamplerPtr = ambient.mSamplerPtr;
	}
	else
	{
		mSamplerPtr = nullptr;
	}
}

AmbientOccluder& AmbientOccluder::operator=(const AmbientOccluder& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mU = rhs.mU;
	mV = rhs.mV;
	mW = rhs.mW;
	mLs = rhs.mLs;
	mColor = rhs.mColor;
	mMinAmount = rhs.mMinAmount;

	if (mSamplerPtr)
	{
		mSamplerPtr.reset();
	}

	if (rhs.mSamplerPtr)
	{
		mSamplerPtr = rhs.mSamplerPtr;
	}
	else
	{
		mSamplerPtr = nullptr;
	}

	mMinAmount = rhs.mMinAmount;

	return *this;
}

std::shared_ptr<AmbientOccluder> AmbientOccluder::Clone() const
{
	return std::make_shared<AmbientOccluder>(*this);
}

Vector3D AmbientOccluder::GetDirection(ShadeRec& sr)
{
	Point3D sp = mSamplerPtr->SampleHemisphere();
	return (sp.mPosX * mU + sp.mPosY * mV + sp.mPosZ * mW);
}

bool AmbientOccluder::InShadow(const Ray& ray, const ShadeRec& sr) const
{
	float t;
	int numObjects = sr.mWorld.mObjects.size();

	for (int j = 0; j < numObjects; j++)
	{
		if (sr.mWorld.mObjects[j]->Shadow_hit(ray, t))
		{
			return true;
		}
	}

	return false;
}

RGBColor AmbientOccluder::L(ShadeRec& sr)
{
	mW = sr.mNormal;
	//jitter up vector in case normal is vertical
	mV = mW ^ Vector3D(0.0072, 1.0, 0.0034);
	mV.Normalize();
	mU = mV ^ mW;

	Ray shadowRay;
	shadowRay.mOrigin = sr.mHitPoint;
	shadowRay.mDirection = GetDirection(sr);

	if (InShadow(shadowRay, sr))
	{
		return mMinAmount * mLs * mColor;
	}
	else
	{
		return mLs * mColor;
	}
}

void AmbientOccluder::SetSampler(std::shared_ptr<Sampler> sPtr)
{
	if (mSamplerPtr)
	{
		mSamplerPtr.reset();
	}

	mSamplerPtr = sPtr;
	mSamplerPtr->MapSamplesToHemisphere(1);
}

void AmbientOccluder::SetRadiance(float l)
{
	mLs = l;
}

void AmbientOccluder::SetColor(RGBColor min)
{
	mColor = min;
}

void AmbientOccluder::SetColor(float a)
{
	mColor = RGBColor(a);
}

void AmbientOccluder::SetColor(float r, float g, float b)
{
	mColor = RGBColor(r, g, b);
}

void AmbientOccluder::SetMinAmount(float ma)
{
	mMinAmount = ma;
}
