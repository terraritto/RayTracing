#include "CookTorrance.h"

CookTorrance::CookTorrance()
	: Material()
{
	mAmbientBRDF = std::make_shared<Lambertian>();
	mDiffuseBRDF = std::make_shared<Lambertian>();
	mSpecularBRDF = std::make_shared<MicrofasetSpecular>();
}

CookTorrance::CookTorrance(const CookTorrance& ph)
	: Material(ph)
{
	if (ph.mAmbientBRDF)
	{
		mAmbientBRDF = ph.mAmbientBRDF->Clone();
	}
	else
	{
		mAmbientBRDF = nullptr;
	}

	if (ph.mDiffuseBRDF)
	{
		mDiffuseBRDF = ph.mDiffuseBRDF->Clone();
	}
	else
	{
		mDiffuseBRDF = nullptr;
	}

	if (ph.mSpecularBRDF)
	{
		mSpecularBRDF = ph.mSpecularBRDF->Clone();
	}
	else
	{
		mDiffuseBRDF = nullptr;
	}
}

CookTorrance::~CookTorrance()
{
}

CookTorrance& CookTorrance::operator=(const CookTorrance& rhs)
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

	if (mSpecularBRDF)
	{
		mSpecularBRDF.reset();
		mSpecularBRDF = nullptr;
	}

	if (rhs.mSpecularBRDF)
	{
		mSpecularBRDF = rhs.mSpecularBRDF->Clone();
	}

	return *this;
}

std::shared_ptr<CookTorrance> CookTorrance::Clone() const
{
	return std::make_shared<CookTorrance>(*this);
}

RGBColor CookTorrance::Shade(ShadeRec& sr)
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
				Ray ShadowRay(sr.mHitPoint, wi);
				inShadow = sr.mWorld.mLights[j]->InShadow(ShadowRay, sr);
			}
			if (!inShadow) {
				L += (mDiffuseBRDF->Func(sr, wo, wi) + mSpecularBRDF->Func(sr, wo, wi))
					* sr.mWorld.mLights[j]->L(sr) * nDotWi;
			}
		}
	}

	return L;
}

RGBColor CookTorrance::AreaLightShade(ShadeRec& sr)
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
				Ray ShadowRay(sr.mHitPoint, wi);
				inShadow = sr.mWorld.mLights[j]->InShadow(ShadowRay, sr);
			}
			if (!inShadow) {
				L += (mDiffuseBRDF->Func(sr, wo, wi) + mSpecularBRDF->Func(sr, wo, wi))
					* sr.mWorld.mLights[j]->L(sr) * sr.mWorld.mLights[j]->G(sr) *
					nDotWi / sr.mWorld.mLights[j]->pdf(sr);
			}
		}
	}

	return L;
}

void CookTorrance::SetKa(float ka)
{
	mAmbientBRDF->SetKd(ka);
}

void CookTorrance::SetKd(float kd)
{
	mDiffuseBRDF->SetKd(kd);
}

void CookTorrance::SetKs(float ks)
{
	mSpecularBRDF->SetKs(ks);
}

void CookTorrance::SetFresnel(float f)
{
	mSpecularBRDF->SetFresnel(f);
}

void CookTorrance::SetType(MicrofaseType type)
{
	mSpecularBRDF->SetType(type);
}

void CookTorrance::SetAlpha(float alpha)
{
	mSpecularBRDF->SetAlpha(alpha);
}

void CookTorrance::SetCd(const RGBColor c)
{
	mAmbientBRDF->SetCd(c);
	mDiffuseBRDF->SetCd(c);
}

void CookTorrance::SetCd(const float r, const float g, const float b)
{
	mAmbientBRDF->SetCd(r, g, b);
	mDiffuseBRDF->SetCd(r, g, b);
}

void CookTorrance::SetCd(const float c)
{
	mAmbientBRDF->SetCd(c);
	mAmbientBRDF->SetCd(c);
}

void CookTorrance::SetCs(const RGBColor c)
{
	mSpecularBRDF->SetCs(c);
}

void CookTorrance::SetCs(const float r, const float g, const float b)
{
	mSpecularBRDF->SetCs(r, g, b);
}

void CookTorrance::SetCs(const float c)
{
	mSpecularBRDF->SetCs(c);
}
