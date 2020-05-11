#include "FresnelReflector.h"

FresnelReflector::FresnelReflector()
	: BRDF()
	, mEtaIn(0.0f)
	, mEtaOut(0.0f)
{
}

FresnelReflector::~FresnelReflector()
{
}

std::shared_ptr<FresnelReflector> FresnelReflector::Clone() const
{
	return std::make_shared<FresnelReflector>(*this);
}

void FresnelReflector::SetEtaIn(const float eta)
{
	mEtaIn = eta;
}

void FresnelReflector::SetEtaOut(const float eta)
{
	mEtaOut = eta;
}

RGBColor FresnelReflector::Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wr) const
{
	return black;
}

RGBColor FresnelReflector::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr) const
{
	float nDotWo = sr.mNormal * wo;
	wr = -wo + 2.0 * sr.mNormal * nDotWo;
	return (Fresnel(sr) * white / std::fabs(sr.mNormal * wr));
}

RGBColor FresnelReflector::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr, float& pdf) const
{
	return black;
}

RGBColor FresnelReflector::Rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return black;
}

float FresnelReflector::Fresnel(const ShadeRec& sr) const
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

	float cosTheta_i= -normal * sr.mRay.mDirection;
	float temp = 1.0 - (1.0 - std::pow(cosTheta_i, 2)) / std::pow(eta, 2);
	float cosTheta_t = std::sqrt(1.0 - (1.0 - std::pow(cosTheta_i, 2)) / std::pow(eta, 2));
	float rParallel = (eta * cosTheta_i - cosTheta_t) / (eta * cosTheta_i + cosTheta_t);
	float rPerpendicular = (cosTheta_i - eta * cosTheta_t) / (cosTheta_i + eta * cosTheta_t);
	float kr = 0.5 * (std::pow(rParallel, 2) + std::pow(rPerpendicular, 2));
	return kr;
}
