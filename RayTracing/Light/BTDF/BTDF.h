#pragma once
#include "../Utility/RGBColor.h"
#include "../Utility/ShadeRec.h"
#include "../Maths/Vector3D.h"

class BTDF
{
public:
	BTDF() = default;
	BTDF(const BTDF& BTDF) = default;
	BTDF& operator=(const BTDF& rhs) = default;
	virtual ~BTDF() = default;

	virtual RGBColor Func(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const = 0;
	virtual RGBColor SampleFunc(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const = 0;
	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const = 0;
	virtual bool tir(const ShadeRec& sr) = 0;
};