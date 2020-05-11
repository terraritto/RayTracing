#include "Transparent.h"

Transparent::Transparent()
	: Phong()
{
	mReflectiveBRDF = std::make_shared<PerfectSpecular>();
	mSpecularBTDF = std::make_shared<PerfectTransmitter>();
}

Transparent::Transparent(const Transparent& tp)
	: Phong(tp)
{
	if (tp.mReflectiveBRDF)
	{
		mReflectiveBRDF = tp.mReflectiveBRDF->Clone();
	}
	else
	{
		mReflectiveBRDF = std::make_shared<PerfectSpecular>();
	}

	if (tp.mSpecularBTDF)
	{
		mSpecularBTDF = tp.mSpecularBTDF->Clone();
	}
	else
	{
		mSpecularBTDF = std::make_shared<PerfectTransmitter>();
	}
}

Transparent::~Transparent()
{
}

Transparent& Transparent::operator=(const Transparent& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Phong::operator=(rhs);

	if (rhs.mReflectiveBRDF)
	{
		mReflectiveBRDF = rhs.mReflectiveBRDF->Clone();
	}

	if (rhs.mSpecularBTDF)
	{
		mSpecularBTDF = rhs.mSpecularBTDF->Clone();
	}

	return *this;
}

std::shared_ptr<Transparent> Transparent::Clone() const
{
	return std::make_shared<Transparent>(*this);
}

RGBColor Transparent::Shade(ShadeRec& sr)
{
	RGBColor L(Phong::Shade(sr));

	Vector3D wo = -sr.mRay.mDirection;
	Vector3D wi;
	RGBColor fr = mReflectiveBRDF->SampleFunc(sr, wo, wi);
	Ray reflected_ray(sr.mHitPoint, wi);

	if (mSpecularBTDF->tir(sr))
	{
		L += sr.mWorld.mTracerPtr->TraceRay(reflected_ray, sr.mDepth + 1);
	}
	else
	{
		Vector3D wt;
		RGBColor ft = mSpecularBTDF->SampleFunc(sr, wo, wt);
		Ray transmitted_ray(sr.mHitPoint, wt);

		L += fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, sr.mDepth + 1) * std::fabs(sr.mNormal * wi);
		L += ft * sr.mWorld.mTracerPtr->TraceRay(transmitted_ray, sr.mDepth + 1) * std::fabs(sr.mNormal * wt);
	}

	return L;
}

void Transparent::SetIor(float ior)
{
	mSpecularBTDF->SetIor(ior);
}

void Transparent::SetKr(float kr)
{
	mReflectiveBRDF->SetKr(kr);
}

void Transparent::SetKt(float kt)
{
	mSpecularBTDF->SetKt(kt);
}
