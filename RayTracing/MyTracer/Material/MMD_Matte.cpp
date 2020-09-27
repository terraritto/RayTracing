#include "MMD_Matte.h"

MMD_Matte::MMD_Matte()
	: Material()
{
	mAmbientBRDF = std::make_shared<Lambertian>();
	mDiffuseBRDF = std::make_shared<Lambertian>();
	mSVDiffuseBRDF = std::make_shared<SV_Lambertian>();
}

MMD_Matte::MMD_Matte(const MMD_Matte& m)
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

	if (m.mSVDiffuseBRDF)
	{
		mSVDiffuseBRDF = m.mSVDiffuseBRDF->Clone();
	}
	else
	{
		mSVDiffuseBRDF.reset();
	}
}

MMD_Matte::~MMD_Matte()
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

MMD_Matte& MMD_Matte::operator=(const MMD_Matte& rhs)
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

	if (mSVDiffuseBRDF)
	{
		mSVDiffuseBRDF.reset();
	}

	if (rhs.mSVDiffuseBRDF)
	{
		mSVDiffuseBRDF = rhs.mSVDiffuseBRDF->Clone();
	}

	return *this;
}

std::shared_ptr<MMD_Matte> MMD_Matte::Clone() const
{
	return std::make_shared<MMD_Matte>(*this);
}

void MMD_Matte::SetKa(const float k)
{
	mAmbientBRDF->SetKa(k);
}

void MMD_Matte::SetKd(const float k)
{
	mDiffuseBRDF->SetKd(k); //supecific diffuse is constant
	mSVDiffuseBRDF->SetKd(k);
}

void MMD_Matte::SetCd(const RGBColor c)
{
	mAmbientBRDF->SetCd(c);
	mDiffuseBRDF->SetCd(c);
}

void MMD_Matte::SetCd(const float r, const float g, const float b)
{
	mAmbientBRDF->SetCd(r, g, b);
	mDiffuseBRDF->SetCd(r, g, b);
}

void MMD_Matte::SetCd(const float c)
{
	mAmbientBRDF->SetCd(c);
	mDiffuseBRDF->SetCd(c);
}

void MMD_Matte::SetCda(const RGBColor c)
{
	mAmbientBRDF->SetCd(c);
}

void MMD_Matte::setCdd(const RGBColor c)
{
	mDiffuseBRDF->SetCd(c);
}

void MMD_Matte::setCddc(const std::shared_ptr<Texture> cd)
{
	mSVDiffuseBRDF->SetCd(cd);
}

void MMD_Matte::SetToon(const std::shared_ptr<Texture> toon)
{
	mSVDiffuseBRDF->SetToon(toon);
}

void MMD_Matte::SetSampler(std::shared_ptr<Sampler> sp)
{
	mDiffuseBRDF->SetSampler(sp);
	mSVDiffuseBRDF->SetSampler(sp);
}

void MMD_Matte::SetSamples(const int numSamples)
{
	mDiffuseBRDF->SetSamples(numSamples);
	mSVDiffuseBRDF->SetSamples(numSamples);
}

RGBColor MMD_Matte::Shade(ShadeRec& sr)
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
				L += mDiffuseBRDF->Func(sr, wo, wi) * mSVDiffuseBRDF->Func(sr,wo,wi) * sr.mWorld.mLights[j]->L(sr) * nDotWi;
			}
		}
	}

	return L;
}

RGBColor MMD_Matte::PathShade(ShadeRec& sr)
{
	Vector3D wi;
	Vector3D wo = -sr.mRay.mDirection;
	float pdf;
	RGBColor f = mDiffuseBRDF->SampleFunc(sr, wo, wi, pdf) * mSVDiffuseBRDF->SampleFunc(sr,wo,wi,pdf);
	float nDotWi = sr.mNormal * wi;
	Ray reflected_ray(sr.mHitPoint, wi);

	return (f * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, sr.mDepth + 1) * nDotWi / pdf);
}

RGBColor MMD_Matte::GlobalShade(ShadeRec& sr)
{
	RGBColor L;

	if (sr.mDepth == 0)
	{
		L = AreaLightShade(sr);
	}

	Vector3D wi;
	Vector3D wo = -sr.mRay.mDirection;
	float pdf;
	RGBColor f = mDiffuseBRDF->SampleFunc(sr, wo, wi, pdf) * mSVDiffuseBRDF->SampleFunc(sr,wo,wi,pdf);
	float nDotWi = sr.mNormal * wi;
	Ray reflected_ray(sr.mHitPoint, wi);

	L += (f * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, sr.mDepth + 1) * nDotWi / pdf);

	return L;
}

RGBColor MMD_Matte::AreaLightShade(ShadeRec& sr)
{
	RGBColor L(0);
	if (GetAlpha(sr) <= 0.1f)
	{
		Ray r(sr.mHitPoint, sr.mRay.mDirection);
		return sr.mWorld.mTracerPtr->TraceRay(r,0);
	}

	Vector3D wo = -sr.mRay.mDirection;
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
				inShadow = sr.mWorld.mLights[j]->InShadowAlpha(shadowRay, sr);
			}

			if (!inShadow)
			{
				L += mDiffuseBRDF->Func(sr, wo, wi) * mSVDiffuseBRDF->Func(sr, wo, wi) * sr.mWorld.mLights[j]->L(sr)
					* sr.mWorld.mLights[j]->G(sr) * mSVDiffuseBRDF->GetToonColor(nDotWi) //toon shaing
					/ sr.mWorld.mLights[j]->pdf(sr);
			}
		}
	}

	 L +=  L * mAmbientBRDF->Rho(sr, wo) * sr.mWorld.mAmbientPtr->L(sr);

	return L;
}

float MMD_Matte::GetAlpha(ShadeRec& sr)
{
	return mSVDiffuseBRDF->GetAlpha(sr);
}
