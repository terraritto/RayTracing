#pragma once
#include "../Material/CookTorrance.h"
#include "../BRDF/PerrfectSpecular.h"

class MicforasetReflective : public CookTorrance
{
public:
	MicforasetReflective();
	MicforasetReflective(const MicforasetReflective& re);
	~MicforasetReflective();
	MicforasetReflective& operator=(const MicforasetReflective& rhs);

	std::shared_ptr<MicforasetReflective> Clone() const;

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