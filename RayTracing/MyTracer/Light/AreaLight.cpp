#include "AreaLight.h"
#include <numeric>

AreaLight::AreaLight()
	: Light()
	, mObjectPtr(nullptr)
	, mMaterialPtr(nullptr)
{
}

AreaLight::AreaLight(const AreaLight& light)
	: Light(light)
{
	if (light.mObjectPtr)
	{
		mObjectPtr = light.mObjectPtr;
	}
	else
	{
		mObjectPtr = nullptr;
	}

	if (light.mMaterialPtr)
	{
		mMaterialPtr = light.mMaterialPtr;
	}
	else
	{
		mMaterialPtr = nullptr;
	}
}

AreaLight::~AreaLight()
{
}

AreaLight& AreaLight::operator=(const AreaLight& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	if(rhs.mObjectPtr)
	{
		mObjectPtr.reset();
		mObjectPtr = rhs.mObjectPtr;
	}

	if (rhs.mMaterialPtr)
	{
		mMaterialPtr.reset();
		mMaterialPtr = rhs.mMaterialPtr;
	}

	return *this;
}

std::shared_ptr<AreaLight> AreaLight::Clone() const
{
	return std::make_shared<AreaLight>(*this);
}

Vector3D AreaLight::GetDirection(ShadeRec& sr)
{
	mSamplePoint = mObjectPtr->Sample();
	mLightNormal = mObjectPtr->GetNormal(mSamplePoint);
	mWi = mSamplePoint - sr.mHitPoint;
	mWi.Normalize();

	return mWi;
}

bool AreaLight::InShadow(const Ray& ray, const ShadeRec& sr) const
{
	float t = std::numeric_limits<float>::max();
	int numObjects = sr.mWorld.mObjects.size();
	float ts = (mSamplePoint - ray.mOrigin) * ray.mDirection;

	for (int j = 0; j < numObjects; j++)
	{
		if (!sr.mWorld.mObjects[j]->GetIsShadow())
		{
			continue;
		}

		if (sr.mWorld.mObjects[j]->Shadow_hit(ray, t) && t < ts)
		{
			return true;
		}
	}

	return false;
}

bool AreaLight::InShadowAlpha(const Ray& ray, ShadeRec& sr)
{
	float t = std::numeric_limits<float>::max();
	int numObjects = sr.mWorld.mObjects.size();
	float ts = (mSamplePoint - ray.mOrigin) * ray.mDirection;

	for (int j = 0; j < numObjects; j++)
	{
		if (!sr.mWorld.mObjects[j]->GetIsShadow())
		{
			continue;
		}

		if (sr.mWorld.mObjects[j]->Shadow_hit(ray, t) && t < ts)
		{
			return true;
		}
	}

	return false;
}

RGBColor AreaLight::L(ShadeRec& sr)
{
	float nDotd = - mLightNormal * mWi;
	if (nDotd > 0.0)
	{
		return mMaterialPtr->GetLe(sr);
	}
	else
	{
		return black;
	}
}

float AreaLight::G(const ShadeRec& sr) const
{
	float nDotd = -mLightNormal * mWi;
	float d2 = mSamplePoint.LengthSq(sr.mHitPoint);

	return nDotd / d2;
}

float AreaLight::pdf(const ShadeRec& sr) const
{
	return mObjectPtr->pdf(sr);
}

void AreaLight::SetObject(std::shared_ptr<GeometricObject> object)
{
	mObjectPtr = object;
	if (mObjectPtr)
	{
		mMaterialPtr = mObjectPtr->GetMaterial();
	}
}
