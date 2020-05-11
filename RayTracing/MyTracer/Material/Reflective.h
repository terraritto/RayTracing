#pragma once
#include "Phong.h"
#include "../BRDF/PerrfectSpecular.h"

class Reflective : public Phong
{
public:
	Reflective();
	Reflective(const Reflective& re);
	~Reflective();
	Reflective& operator=(const Reflective& rhs);

	std::shared_ptr<Reflective> Clone() const;

	void SetKr(const float k);
	void SetCr(const RGBColor& c);
	void SetCr(const float r, const float g, const float b);
	void SetCr(const float c);

	RGBColor Shade(ShadeRec& s) override;
	RGBColor PathShade(ShadeRec& sr) override;
	RGBColor GlobalShade(ShadeRec& sr) override;
	RGBColor AreaLightShade(ShadeRec& sr) override;
private:
	std::shared_ptr<PerfectSpecular> mReflectiveBRDF;
};