#include "Phong.h"

Phong::Phong()
	: Material()
{
	mAmbientBRDF = std::make_shared<Lambertian>();
	mDiffuseBRDF = std::make_shared<Lambertian>();
	mSpecularBRDF = std::make_shared<GlossySpecular>();
}

Phong::Phong(const Phong& ph)
	:Material(ph)
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

Phong::~Phong()
{

}

Phong& Phong::operator=(const Phong& rhs)
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

std::shared_ptr<Phong> Phong::Clone() const
{
	return std::make_shared<Phong>(*this);
}

RGBColor Phong::Shade(ShadeRec& sr)
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

RGBColor Phong::AreaLightShade(ShadeRec& sr)
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

void Phong::SetKa(float ka)
{
	mAmbientBRDF->SetKd(ka);
}

void Phong::SetKd(float kd)
{
	mDiffuseBRDF->SetKd(kd);
}

void Phong::SetKs(float ks)
{
	mSpecularBRDF->SetKs(ks);
}

void Phong::SetExp(float exp)
{
	mSpecularBRDF->SetExp(exp);
}

void Phong::SetCd(const RGBColor c)
{
	mAmbientBRDF->SetCd(c);
	mDiffuseBRDF->SetCd(c);
}

void Phong::SetCd(const float r, const float g, const float b)
{
	mAmbientBRDF->SetCd(r, g, b);
	mDiffuseBRDF->SetCd(r, g, b);
}

void Phong::SetCd(const float c)
{
	mAmbientBRDF->SetCd(c);
	mDiffuseBRDF->SetCd(c);
}

void Phong::SetCs(const RGBColor c)
{
	mSpecularBRDF->SetCs(c);
}

void Phong::SetCs(const float r, const float g, const float b)
{
	mSpecularBRDF->SetCs(r, g, b);
}

void Phong::SetCs(const float c)
{
	mSpecularBRDF->SetCs(c);
}
