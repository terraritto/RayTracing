#pragma once
#include "Material.h"
#include "../BRDF/Lambertian.h"

class Matte : public Material
{
public:
	Matte();
	Matte(const Matte& m);
	~Matte();
	Matte& operator=(const Matte& rhs);

	std::shared_ptr<Matte> Clone() const;

	void SetKa(const float k);
	void SetKd(const float k);
	void SetCd(const RGBColor c);
	void SetCd(const float r, const float g, const float b);
	void SetCd(const float c);

	void SetSampler(std::shared_ptr<Sampler> sp);
	void SetSamples(const int numSamples);

	RGBColor Shade(ShadeRec& sr) override;
	RGBColor PathShade(ShadeRec& sr) override;
	RGBColor GlobalShade(ShadeRec& sr) override;
	RGBColor AreaLightShade(ShadeRec& sr) override;
private:
	std::shared_ptr<Lambertian> mAmbientBRDF;
	std::shared_ptr<Lambertian> mDiffuseBRDF;
};