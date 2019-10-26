#include "..\Material\Plastic.h"

Plastic::Plastic()
	: Material()
{
	mAmbientBRDF = std::make_shared<BRDF>();
	mDiffuseBRDF = std::make_shared<BRDF>();
	mSpecularBRDF = std::make_shared<BRDF>();
}


Plastic::Plastic(const Plastic& pl)
	: Material(pl)
{
	if (pl.mAmbientBRDF)
	{
		mAmbientBRDF = pl .mAmbientBRDF->Clone();
	}
	else
	{
		mAmbientBRDF = nullptr;
	}

	if (pl.mDiffuseBRDF)
	{
		mDiffuseBRDF = pl.mDiffuseBRDF->Clone();
	}
	else
	{
		mDiffuseBRDF = nullptr;
	}

	if (pl.mSpecularBRDF)
	{
		mSpecularBRDF = pl.mSpecularBRDF->Clone();
	}
	else
	{
		mDiffuseBRDF = nullptr;
	}
}

Plastic::~Plastic()
{

}

Plastic& Plastic::operator=(const Plastic& rhs)
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

std::shared_ptr<Plastic> Plastic::Clone() const
{
	return std::make_shared<Plastic>(*this);
}

RGBColor Plastic::Shade(ShadeRec& sr)
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
			L += (mDiffuseBRDF->Func(sr, wo, wi) + mSpecularBRDF->Func(sr, wo, wi))
				* sr.mWorld.mLights[j]->L(sr) * nDotWi;
		}
	}

	return L;
}

void Plastic::SetAmbientBRDF(std::shared_ptr<BRDF> brdf)
{
	mAmbientBRDF = brdf;
}

void Plastic::SetDiffuseBRDF(std::shared_ptr<BRDF> brdf)
{
	mDiffuseBRDF = brdf;
}

void Plastic::SetSpecularBRDF(std::shared_ptr<BRDF> brdf)
{
	mSpecularBRDF = brdf;
}
