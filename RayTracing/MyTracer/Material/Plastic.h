#pragma once
#include "Material.h"
#include "../BRDF/BRDF.h"

class Plastic :public Material
{
public:
	Plastic();
	Plastic(const Plastic& pl);
	~Plastic();
	Plastic& operator=(const Plastic& rhs);
	
	std::shared_ptr<Plastic> Clone() const;

	RGBColor Shade(ShadeRec& sr) override;

	void SetAmbientBRDF(std::shared_ptr<BRDF> brdf);
	void SetDiffuseBRDF(std::shared_ptr<BRDF> brdf);
	void SetSpecularBRDF(std::shared_ptr<BRDF> brdf);
private:
	std::shared_ptr<BRDF> mAmbientBRDF;
	std::shared_ptr<BRDF> mDiffuseBRDF;
	std::shared_ptr<BRDF> mSpecularBRDF;
};