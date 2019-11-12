#pragma once
#include "Material.h"

class Emissive : public Material
{
public:
	Emissive();
	Emissive(const Emissive& e);
	~Emissive();
	Emissive& operator=(const Emissive& rhs);

	std::shared_ptr<Emissive> Clone() const;

	void SetLadiance(const float ls);
	void SetCe(const RGBColor c);
	void SetCe(const float r, const float g, const float b);
	void SetCe(const float c);
	RGBColor Shade(ShadeRec& sr) override;
	RGBColor AreaLightShade(ShadeRec& sr) override;
	RGBColor GetLe(ShadeRec& sr) const override;
private:
	float mLs; //radiance scaling vector
	RGBColor mCe; //color
};