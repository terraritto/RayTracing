#pragma once
#include "MMD_Matte.h"
#include "../BRDF/FresnelReflector.h"
#include "../BTDF/FresnelTransmitter.h"

class MMD_Dielectric : public MMD_Matte
{
public:
	MMD_Dielectric();
	MMD_Dielectric(const MMD_Dielectric& tp);
	~MMD_Dielectric();
	MMD_Dielectric& operator=(const MMD_Dielectric& rhs);

	std::shared_ptr<MMD_Dielectric> Clone() const;

	RGBColor Shade(ShadeRec& sr) override;
	RGBColor AreaLightShade(ShadeRec& sr) override;

	void SetEtaIn(float eta);
	void SetEtaOut(float eta);
	void SetCfIn(const RGBColor& color);
	void SetCfIn(const float color);
	void SetCfIn(const float r, const float g, const float b);
	void SetCfOut(const RGBColor& color);
	void SetCfOut(const float color);
	void SetCfOut(const float r, const float g, const float b);
private:
	RGBColor mCfIn;
	RGBColor mCfOut;

	std::shared_ptr<FresnelReflector> mFresnelBRDF;
	std::shared_ptr<FresnelTransmitter> mFresnelBTDF;
};