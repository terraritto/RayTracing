#pragma once
#pragma once
#include "Material.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/MicrofasetSpecular.h"

class CookTorrance : public Material
{
public:
	CookTorrance();
	CookTorrance(const CookTorrance& ph);
	virtual ~CookTorrance();
	CookTorrance& operator=(const CookTorrance& rhs);

	std::shared_ptr<CookTorrance> Clone() const;

	virtual RGBColor Shade(ShadeRec& s) override;
	virtual RGBColor AreaLightShade(ShadeRec& sr) override;

	void SetKa(float ka);
	void SetKd(float kd);
	void SetKs(float ks);
	void SetFresnel(float f);
	void SetType(MicrofaseType type);
	void SetAlpha(float alpha);
	void SetCd(const RGBColor c);
	void SetCd(const float r, const float g, const float b);
	void SetCd(const float c);
	void SetCs(const RGBColor c);
	void SetCs(const float r, const float g, const float b);
	void SetCs(const float c);
protected:
	std::shared_ptr<Lambertian> mAmbientBRDF;
	std::shared_ptr<Lambertian> mDiffuseBRDF;
	std::shared_ptr<MicrofasetSpecular> mSpecularBRDF;
};