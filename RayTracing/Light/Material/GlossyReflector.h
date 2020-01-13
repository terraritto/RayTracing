#pragma once
#include "Phong.h"

class GlossyReflector : public Phong
{
public:
	GlossyReflector();
	GlossyReflector(const GlossyReflector& re);
	~GlossyReflector();
	GlossyReflector& operator=(const GlossyReflector& rhs);

	std::shared_ptr<GlossyReflector> Clone() const;

	void SetSampler(std::shared_ptr<Sampler> sp, const float exp);
	void SetSamples(const int numSamples, const float exp);
	void SetKr(const float k);
	void SetCr(const RGBColor r);
	void SetCr(const float r, const float g, const float b);
	void SetCr(const float c);
	void SetExponent(const float exp);

	RGBColor AreaLightShade(ShadeRec& sr) override;
private:
	std::shared_ptr<GlossySpecular> mGlossySpecularBRDF;
};