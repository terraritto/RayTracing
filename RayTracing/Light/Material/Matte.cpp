#include "Matte.h"

Matte::Matte()
	: Material()
{
	mAmbientBRDF = std::make_shared<Lambertian>();
	mDiffuseBRDF = std::make_shared<Lambertian>();
}

Matte::Matte(const Matte& m)
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

Matte::~Matte()
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

Matte& Matte::operator=(const Matte& rhs)
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

std::shared_ptr<Matte> Matte::Clone() const
{
	return std::make_shared<Matte>(*this);
}

void Matte::SetKa(const float k)
{
	mAmbientBRDF->SetKd(k);
}

void Matte::SetKd(const float k)
{
	mDiffuseBRDF->SetKd(k);
}

void Matte::SetCd(const RGBColor c)
{
	mAmbientBRDF->SetCd(c);
	mDiffuseBRDF->SetCd(c);
}

void Matte::SetCd(const float r, const float g, const float b)
{
	mAmbientBRDF->SetCd(r, g, b);
	mDiffuseBRDF->SetCd(r, g, b);
}

void Matte::SetCd(const float c)
{
	mAmbientBRDF->SetCd(c);
	mDiffuseBRDF->SetCd(c);
}

RGBColor Matte::Shade(ShadeRec& sr)
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

RGBColor Matte::AreaLightShade(ShadeRec& sr)
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
