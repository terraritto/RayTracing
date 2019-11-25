#include "EnvironmentLight.h"

EnvironmentLight::EnvironmentLight()
	: Light()
	, mSamplerPtr(nullptr)
	, mMaterialPtr(nullptr)
	, mU(), mV(), mW()
	, mWi()
{
}

EnvironmentLight::EnvironmentLight(const EnvironmentLight& light)
	: Light(light)
	, mU(light.mU), mV(light.mV), mW(light.mW)
	, mWi(light.mW)
{
	if (light.mSamplerPtr)
	{
		mSamplerPtr = light.mSamplerPtr->Clone();
	}
	else
	{
		mSamplerPtr = nullptr;
	}

	if (light.mMaterialPtr)
	{
		mMaterialPtr = light.mMaterialPtr->Clone();
	}
	else
	{
		mMaterialPtr = nullptr;
	}
}

EnvironmentLight::~EnvironmentLight()
{
}

EnvironmentLight& EnvironmentLight::operator=(const EnvironmentLight& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Light::operator=(rhs);

	if (rhs.mSamplerPtr)
	{
		mSamplerPtr = rhs.mSamplerPtr->Clone();
	}

	if (rhs.mMaterialPtr)
	{
		mMaterialPtr = rhs.mMaterialPtr->Clone();
	}

	return *this;
}

std::shared_ptr<EnvironmentLight> EnvironmentLight::Clone()
{
	return std::make_shared<EnvironmentLight>(*this);
}

void EnvironmentLight::SetSampler(std::shared_ptr<Sampler> sampler)
{
	mSamplerPtr = sampler;
	mSamplerPtr->MapSamplesToHemisphere(1);
}

void EnvironmentLight::SetMaterial(std::shared_ptr<Material> material)
{
	mMaterialPtr = material;
}

Vector3D EnvironmentLight::GetDirection(ShadeRec& sr)
{
	mW = sr.mNormal;
	mV = Vector3D(0.0034, 1, 0.0071) ^ mW;
	mV.Normalize();
	mU = mV ^ mW;
	Point3D sp = mSamplerPtr->SampleHemisphere();
	mWi = sp.mPosX * mU + sp.mPosY * mV + sp.mPosZ * mW;

	return mWi;
}

RGBColor EnvironmentLight::L(ShadeRec& sr)
{
	return mMaterialPtr->GetLe(sr);
}

bool EnvironmentLight::InShadow(const Ray& ray, const ShadeRec& sr) const
{
	float t;
	int numObjects = sr.mWorld.mObjects.size();

	for (int j = 0; j < numObjects; j++)
	{
		if (!sr.mWorld.mObjects[j]->GetIsShadow())
		{
			continue;
		}

		if (sr.mWorld.mObjects[j]->Shadow_hit(ray, t))
		{
			return true;
		}
	}

	return false;
}

float EnvironmentLight::pdf(const ShadeRec& sr) const
{
	return sr.mNormal * mWi * INVPI;
}
