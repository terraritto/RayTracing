#include "FresnelTransmitter.h"

FresnelTransmitter::FresnelTransmitter()
	: BTDF()
	, mEtaIn(0.0f)
	, mEtaOut(0.0f)
{
}

FresnelTransmitter::FresnelTransmitter(const FresnelTransmitter& ft)
	: BTDF(ft)
	, mEtaIn(ft.mEtaIn)
	, mEtaOut(ft.mEtaOut)
{
}

std::shared_ptr<FresnelTransmitter> FresnelTransmitter::Clone() const
{
	return std::make_shared<FresnelTransmitter>(*this);
}

FresnelTransmitter& FresnelTransmitter::operator=(const FresnelTransmitter& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mEtaIn = rhs.mEtaIn;
	mEtaOut = rhs.mEtaOut;

	return *this;
}

FresnelTransmitter::~FresnelTransmitter()
{
}

RGBColor FresnelTransmitter::Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return black;
}

RGBColor FresnelTransmitter::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const
{
	Normal n(sr.mNormal);
	float cos_theta_i = n * wo;
	float eta;

	// hit inside
	if (cos_theta_i < 0.0)
	{
		cos_theta_i = -cos_theta_i;
		n = -n;
		eta = mEtaOut / mEtaIn;
	}
	else
	{
		eta = mEtaIn / mEtaOut;
	}

	float temp = 1.0 - (1.0 - std::pow(cos_theta_i, 2)) / (std::pow(eta, 2));
	float cos_theta_2 = std::sqrt(temp);
	wt = -wo / eta - (cos_theta_2 - static_cast<double>(cos_theta_i / eta))* n;

	return Fresnel(sr) / std::pow(eta, 2) * white / std::fabs(sr.mNormal * wt);

}

RGBColor FresnelTransmitter::Rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return black;
}

bool FresnelTransmitter::tir(const ShadeRec& sr)
{
	Vector3D wo(-sr.mRay.mDirection);
	float cos_theta_i = sr.mNormal * wo;
	float eta;

	if (cos_theta_i < 0.0)
	{
		eta = mEtaOut / mEtaIn;
	}
	else
	{
		eta = mEtaIn / mEtaOut;
	}

	return (1.0 - (1.0 - std::pow(cos_theta_i, 2)) / (std::pow(eta, 2)) < 0.0);
}

float FresnelTransmitter::Fresnel(const ShadeRec& sr) const
{
	Normal normal(sr.mNormal);
	float nDotD = -normal * sr.mRay.mDirection;
	float eta;

	if (nDotD < 0.0)
	{
		normal = -normal;
		eta = mEtaOut / mEtaIn;
	}
	else
	{
		eta = mEtaIn / mEtaOut;
	}

	float cosTheta_i = -normal * sr.mRay.mDirection;
	float temp = 1.0 - (1.0 - std::pow(cosTheta_i, 2)) / std::pow(eta, 2);
	float cosTheta_t = std::sqrt(1.0 - (1.0 - std::pow(cosTheta_i, 2)) / std::pow(eta, 2));
	float rParallel = (eta * cosTheta_i - cosTheta_t) / (eta * cosTheta_i + cosTheta_t);
	float rPerpendicular = (cosTheta_i - eta * cosTheta_t) / (cosTheta_i + eta * cosTheta_t);
	float kr = 0.5 * (std::pow(rParallel, 2) + std::pow(rPerpendicular, 2));
	float kt = 1 - kr;
	return kt;
}

void FresnelTransmitter::SetEtaIn(const float eta)
{
	mEtaIn = eta;
}

void FresnelTransmitter::SetEtaOut(const float eta)
{
	mEtaOut = eta;
}
