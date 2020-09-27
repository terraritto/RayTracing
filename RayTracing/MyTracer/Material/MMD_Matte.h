#pragma once
#include "Material.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/SV_Lambertian.h"

class MMD_Matte : public Material
{
public:
	MMD_Matte();
	MMD_Matte(const MMD_Matte& m);
	~MMD_Matte();
	MMD_Matte& operator=(const MMD_Matte& rhs);

	std::shared_ptr<MMD_Matte> Clone() const;

	void SetKa(const float k);
	void SetKd(const float k);
	void SetCd(const RGBColor c);
	void SetCd(const float r, const float g, const float b);
	void SetCd(const float c);

	void SetCda(const RGBColor c);
	void setCdd(const RGBColor c);
	void setCddc(const std::shared_ptr<Texture> cd);

	void SetToon(const std::shared_ptr<Texture> toon);

	void SetSampler(std::shared_ptr<Sampler> sp);
	void SetSamples(const int numSamples);

	RGBColor Shade(ShadeRec& sr) override;
	RGBColor PathShade(ShadeRec& sr) override;
	RGBColor GlobalShade(ShadeRec& sr) override;
	RGBColor AreaLightShade(ShadeRec& sr) override;
	float GetAlpha(ShadeRec& sr) override;
protected:
	std::shared_ptr<Lambertian> mAmbientBRDF;
	std::shared_ptr<Lambertian> mDiffuseBRDF;
	std::shared_ptr<SV_Lambertian> mSVDiffuseBRDF;
};