#include "Lambertian.h"
#include "..//Maths/Constants.h"

Lambertian::Lambertian()
	: BRDF()
	, mKd(0.0)
	, mCd(0.0)
{

}

Lambertian::Lambertian(const Lambertian& lamb)
	: BRDF(lamb)
	, mKd(lamb.mKd)
	, mCd(lamb.mCd)
{

}

Lambertian& Lambertian::operator=(const Lambertian& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	BRDF::operator=(rhs);

	mKd = rhs.mKd;
	mCd = rhs.mCd;

	return *this;
}

Lambertian::~Lambertian()
{

}

std::shared_ptr<Lambertian> Lambertian::Clone() const
{
	return std::make_shared<Lambertian>(*this);
}

RGBColor Lambertian::Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return mKd * mCd * INVPI;
}

RGBColor Lambertian::SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const
{
	return mKd * mCd * INVPI;
}

RGBColor Lambertian::Rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return mKd * mCd;
}

void Lambertian::SetKa(const float ka)
{
	mKd = ka;
}

void Lambertian::SetKd(const float kd)
{
	mKd = kd;
}

void Lambertian::SetCd(const RGBColor& c)
{
	mCd = c;
}

void Lambertian::SetCd(const float r, const float g, const float b)
{
	mCd.mRed = r;
	mCd.mBlue = b;
	mCd.mGreen = g;
}

void Lambertian::SetCd(const float c)
{
	mCd.mRed = c;
	mCd.mGreen = c;
	mCd.mBlue = c;
}

