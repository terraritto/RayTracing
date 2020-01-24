#include "Dielectric.h"

Dielectric::Dielectric()
{
	mFresnelBRDF = std::make_shared<FresnelReflector>();
	mFresnelBTDF = std::make_shared<FresnelTransmitter>();
}

Dielectric::Dielectric(const Dielectric& tp)
	: Phong(tp)
{
	if (tp.mFresnelBRDF)
	{
		mFresnelBRDF = tp.mFresnelBRDF->Clone();
	}
	else
	{
		mFresnelBRDF = std::make_shared<FresnelReflector>();
	}

	if (tp.mFresnelBTDF)
	{
		mFresnelBTDF = tp.mFresnelBTDF->Clone();
	}
	else
	{
		mFresnelBTDF = std::make_shared<FresnelTransmitter>();
	}
}

Dielectric::~Dielectric()
{
}

Dielectric& Dielectric::operator=(const Dielectric& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Phong::operator=(rhs);

	if (rhs.mFresnelBRDF)
	{
		mFresnelBRDF = rhs.mFresnelBRDF->Clone();
	}

	if (rhs.mFresnelBTDF)
	{
		mFresnelBTDF = rhs.mFresnelBTDF->Clone();
	}

	mCfIn = rhs.mCfIn;
	mCfOut = rhs.mCfOut;

	return *this;
}

std::shared_ptr<Dielectric> Dielectric::Clone() const
{
	return std::make_shared<Dielectric>(*this);
}

RGBColor Dielectric::Shade(ShadeRec& sr)
{
	RGBColor L(Phong::Shade(sr));

	Vector3D wi;
	Vector3D wo(-sr.mRay.mDirection);
	RGBColor fr = mFresnelBRDF->SampleFunc(sr, wo, wi);
	Ray reflected_ray(sr.mHitPoint, wi);
	float t;
	RGBColor Lr, Lt;
	float ndotwi = sr.mNormal * wi;

	if (mFresnelBTDF->tir(sr)) //total internal reflection
	{
		if (ndotwi < 0.0) {
			//reflected ray is inside
			Lr = sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1);
			L += mCfIn.PowColor(t) * Lr;
		}
		else
		{
			//reflected ray is outside
			Lr = sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1);
			L += mCfOut.PowColor(t) * Lr;
		}
	}
	else
	{
		Vector3D wt;
		RGBColor ft = mFresnelBTDF->SampleFunc(sr, wo, wt);
		Ray transmitted_ray(sr.mHitPoint, wt);
		float ndotwt = sr.mNormal * wt;

		if (ndotwi < 0.0)
		{
			//reflected ray is inside
			Lr = fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1) * std::fabs(ndotwi);
			L += mCfIn.PowColor(t) * Lr;

			// transmitted ray is outside
			Lt = ft * sr.mWorld.mTracerPtr->TraceRay(transmitted_ray, t, sr.mDepth + 1) * std::fabs(ndotwt);
			L += mCfOut.PowColor(t) * Lt;
		}
		else
		{
			//reflected ray is outside
			Lr = fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1) * std::fabs(ndotwi);
			L += mCfOut.PowColor(t) * Lr;

			//transmitted ray is inside
			Lt = ft * sr.mWorld.mTracerPtr->TraceRay(transmitted_ray, t, sr.mDepth + 1) * std::fabs(ndotwt);
			L += mCfIn.PowColor(t) * Lt;
		}
	}

	return L;
}

void Dielectric::SetEtaIn(float eta)
{
	mFresnelBRDF->SetEtaIn(eta);
	mFresnelBTDF->SetEtaIn(eta);
}

void Dielectric::SetEtaOut(float eta)
{
	mFresnelBRDF->SetEtaOut(eta);
	mFresnelBTDF->SetEtaOut(eta);
}

void Dielectric::SetCfIn(const RGBColor& color)
{
	mCfIn = color;
}

void Dielectric::SetCfIn(const float color)
{
	mCfIn = RGBColor(color);
}

void Dielectric::SetCfIn(const float r, const float g, const float b)
{
	mCfIn = RGBColor(r, g, b);
}

void Dielectric::SetCfOut(const RGBColor& color)
{
	mCfOut = color;
}

void Dielectric::SetCfOut(const float color)
{
	mCfOut = RGBColor(color);
}

void Dielectric::SetCfOut(const float r, const float g, const float b)
{
	mCfOut = RGBColor(r, g, b);
}