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
	RGBColor Shade(ShadeRec& sr) override;
private:
	std::shared_ptr<Lambertian> mAmbientBRDF;
	std::shared_ptr<Lambertian> mDiffuseBRDF;
};