#include "SV_Matte.h"

SV_Matte::SV_Matte()
	: Material()
{
	mAmbientBRDF = std::make_shared<SV_Lambertian>();
	mDiffuseBRDF = std::make_shared<SV_Lambertian>();
}

SV_Matte::SV_Matte(const SV_Matte& m)
	:Material(m)
{
	if (m.mAmbientBRDF)
	{
		mAmbientBRDF = m.mAmbientBRDF->Clone();
	}
	else
	{
		mAmbientBRDF = nullptr;
	}

	if (m.mDiffuseBRDF)
	{
		mDiffuseBRDF = m.mDiffuseBRDF->Clone();
	}
	else
	{
		mDiffuseBRDF = nullptr;
	}
}

SV_Matte::~SV_Matte()
{
	if (mAmbientBRDF)
	{
		mAmbientBRDF.reset();
	}

	if (mDiffuseBRDF)
	{
		mDiffuseBRDF.reset();
	}
}

SV_Matte& SV_Matte::operator=(const SV_Matte& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Material::operator=(rhs);

	if (mAmbientBRDF)
	{
		mAmbientBRDF.reset();
		mAmbientBRDF = nullptr;
	}

	if (rhs.mAmbientBRDF)
	{
		mAmbientBRDF = rhs.mAmbientBRDF->Clone();
	}

	if (mDiffuseBRDF)
	{
		mDiffuseBRDF.reset();
		mDiffuseBRDF = nullptr;
	}

	if (rhs.mDiffuseBRDF)
	{
		mDiffuseBRDF = rhs.mDiffuseBRDF->Clone();
	}

	return *this;
}

std::shared_ptr<SV_Matte> SV_Matte::Clone() const
{
	return std::make_shared<SV_Matte>(*this);
}

void SV_Matte::SetKa(const float k)
{
	mAmbientBRDF->SetKa(k);
}

void SV_Matte::SetKd(const float k)
{
	mDiffuseBRDF->SetKd(k);
}

void SV_Matte::SetCd(const std::shared_ptr<Texture> tex)
{
	mAmbientBRDF->SetCd(tex);
	mDiffuseBRDF->SetCd(tex);
}

void SV_Matte::SetSampler(std::shared_ptr<Sampler> sp)
{
	mDiffuseBRDF->SetSampler(sp);
}

void SV_Matte::SetSamples(const int numSamples)
{
	mDiffuseBRDF->SetSamples(numSamples);
}

RGBColor SV_Matte::Shade(ShadeRec& sr)
{
	Vector3D wo = -sr.mRay.mDirection;
	RGBColor L = mAmbientBRDF->Rho(sr, wo) * sr.mWorld.mAmbientPtr->L(sr);
	int numLights = sr.mWorld.mLights.size();

	for (int j = 0; j < numLights; j++)
	{
		Vector3D wi = sr.mWorld.mLights[j]->GetDirection(sr);
		float nDotWi = sr.mNormal * wi;

		if (nDotWi > 0.0)
		{
			bool inShadow = false;

			if (sr.mWorld.mLights[j]->GetIsShadow())
			{
				Ray shadowRay(sr.mHitPoint, wi);
				inShadow = sr.mWorld.mLights[j]->InShadow(shadowRay, sr);
			}
			if (!inShadow)
			{
				L += mDiffuseBRDF->Func(sr, wo, wi) * sr.mWorld.mLights[j]->L(sr) * nDotWi;
			}
		}
	}

	return L;
}

RGBColor SV_Matte::PathShade(ShadeRec& sr)
{
	Vector3D wi;
	Vector3D wo = -sr.mRay.mDirection;
	float pdf;
	RGBColor f = mDiffuseBRDF->SampleFunc(sr, wo, wi, pdf);
	float nDotWi = sr.mNormal * wi;
	Ray reflected_ray(sr.mHitPoint, wi);

	return (f * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, sr.mDepth + 1) * nDotWi / pdf);
}

RGBColor SV_Matte::GlobalShade(ShadeRec& sr)
{
	RGBColor L;

	if (sr.mDepth == 0)
	{
		L = AreaLightShade(sr);
	}

	Vector3D wi;
	Vector3D wo = -sr.mRay.mDirection;
	float pdf;
	RGBColor f = mDiffuseBRDF->SampleFunc(sr, wo, wi, pdf);
	float nDotWi = sr.mNormal * wi;
	Ray reflected_ray(sr.mHitPoint, wi);

	L += (f * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, sr.mDepth + 1) * nDotWi / pdf);

	return L;
}

RGBColor SV_Matte::AreaLightShade(ShadeRec& sr)
{
	Vector3D wo = -sr.mRay.mDirection;
	RGBColor L = mAmbientBRDF->Rho(sr, wo) * sr.mWorld.mAmbientPtr->L(sr);
	int numLights = sr.mWorld.mLights.size();

	for (int j = 0; j < numLights; j++)
	{
		Vector3D wi = sr.mWorld.mLights[j]->GetDirection(sr);
		float nDotWi = sr.mNormal * wi;
		if (nDotWi > 0.0)
		{
			bool inShadow = false;
			if (sr.mWorld.mLights[j]->GetIsShadow())
			{
				Ray shadowRay(sr.mHitPoint, wi);
				inShadow = sr.mWorld.mLights[j]->InShadow(shadowRay, sr);
			}

			if (!inShadow)
			{
				L += mDiffuseBRDF->Func(sr, wo, wi) * sr.mWorld.mLights[j]->L(sr)
					* sr.mWorld.mLights[j]->G(sr) * nDotWi /
					sr.mWorld.mLights[j]->pdf(sr);
			}
		}
	}

	return L;
}
