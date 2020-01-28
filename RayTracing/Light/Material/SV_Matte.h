#pragma once
#include "Material.h"
#include "../BRDF/SV_Lambertian.h"

class SV_Matte : public Material
{
public:
	SV_Matte();
	SV_Matte(const SV_Matte& m);
	~SV_Matte();
	SV_Matte& operator=(const SV_Matte& rhs);

	std::shared_ptr<SV_Matte> Clone() const;

	void SetKa(const float k);
	void SetKd(const float k);
	void SetCd(const std::shared_ptr<Texture> tex);

	void SetSampler(std::shared_ptr<Sampler> sp);
	void SetSamples(const int numSamples);

	RGBColor Shade(ShadeRec& sr) override;
	RGBColor PathShade(ShadeRec& sr) override;
	RGBColor GlobalShade(ShadeRec& sr) override;
	RGBColor AreaLightShade(ShadeRec& sr) override;
private:
	std::shared_ptr<SV_Lambertian> mAmbientBRDF;
	std::shared_ptr<SV_Lambertian> mDiffuseBRDF;
};