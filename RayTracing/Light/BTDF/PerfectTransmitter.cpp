#include "PerfectTransmitter.h"

PerfectTransmitter::PerfectTransmitter()
	: BTDF()
	, mKt(1.0f)
	, mIor(1.0f)
{
}

PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter& pt)
	: BTDF(pt)
	, mKt(pt.mKt)
	, mIor(pt.mIor)
{
}

std::shared_ptr<PerfectTransmitter> PerfectTransmitter::Clone() const
{
	return std::make_shared<PerfectTransmitter>(*this);
}

PerfectTransmitter& PerfectTransmitter::operator=(const PerfectTransmitter& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mKt = rhs.mKt;
	mIor = rhs.mIor;

	return *this;
}

PerfectTransmitter::~PerfectTransmitter()
{
}

RGBColor PerfectTransmitter::Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return black;
}

RGBColor PerfectTransmitter::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const
{
	Normal n(sr.mNormal);
	float cos_theta_i = n * wo;
	float eta = mIor;

	// hit inside
	if (cos_theta_i < 0.0)
	{
		cos_theta_i = -cos_theta_i;
		n = -n;
		eta = 1.0 / eta;
	}

	float temp = 1.0 - (1.0 - std::pow(cos_theta_i, 2)) / (std::pow(eta, 2));
	float cos_theta_2 = std::sqrt(temp);
	wt = -wo / eta - (cos_theta_2 - static_cast<double>(cos_theta_i / eta)) * n;
	
	return mKt / std::pow(eta, 2) * white / std::fabs(sr.mNormal * wt);
}

RGBColor PerfectTransmitter::Rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return black;
}

bool PerfectTransmitter::tir(const ShadeRec& sr)
{
	Vector3D wo(-sr.mRay.mDirection);
	float cos_theta_i = sr.mNormal * wo;
	float eta = mIor;

	if (cos_theta_i < 0.0)
	{
		eta = 1.0 / eta;
	}

	return (1.0 - (1.0 - std::pow(cos_theta_i, 2)) / (std::pow(eta, 2)) < 0.0);
}

void PerfectTransmitter::SetKt(const float kt)
{
	mKt = kt;
}

void PerfectTransmitter::SetIor(const float ior)
{
	mIor = ior;
}
