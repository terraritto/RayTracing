#pragma once
#include "Material.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/GlossySpecular.h"

class Phong : public Material
{
public:
	Phong();
	Phong(const Phong& ph);
	~Phong();
	Phong& operator=(const Phong& rhs);

	std::shared_ptr<Phong> Clone() const;

	virtual RGBColor Shade(ShadeRec& s) override;
	virtual RGBColor AreaLightShade(ShadeRec& sr) override;

	void SetKa(float ka);
	void SetKd(float kd);
	void SetKs(float ks);
	void SetExp(float exp);
	void SetCd(const RGBColor c);
	void SetCd(const float r, const float g, const float b);
	void SetCd(const float c);
	void SetCs(const RGBColor c);
	void SetCs(const float r, const float g, const float b);
	void SetCs(const float c);
protected:
	std::shared_ptr<Lambertian> mAmbientBRDF;
	std::shared_ptr<Lambertian> mDiffuseBRDF;
	std::shared_ptr<GlossySpecular> mSpecularBRDF;
};